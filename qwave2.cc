#include "qwave2.h"
#include <QApplication>
#include <QLabel>
#include <QSizePolicy>
#include <QFileDialog>
#include <QMessageBox>
#include <QHBoxLayout>

#include <WaveformVRuler.h>
#include <iostream>
using namespace std;
//#ifdef _MSC_VER
//#include <QWave2/SndPlayerDirectSound.h>
//#else

//#endif
//#include <cmath>
//#include <math.h>

using namespace QWave2;


MyWidget::MyWidget()
  : QWidget(),
	layout(new QVBoxLayout(this)),

//#ifdef _MSC_VER
//    player(new PLAYERIMPLEMENTATION(this->winId())),
//#else
    //player(new PLAYERIMPLEMENTATION()),
//#endif
    player(new PSndPlayer),
    cursor(new WaveformCursorProxy(this)),
    selection(new WaveformSelectionProxy(this)),
    paused(false),
    hasRuler(false)//Flag fuer zustand von Horizontal Ruler

{
  //waveFormThread = new WaveFormThread;
    soundfile = 0;
  player->initPlayer();
  player->enableTicker();
  outDevices = player->getOutputDevices();

  QHBoxLayout* l;

  l = new QHBoxLayout();
  l->addWidget(new QLabel("Audio File:", this));
  fileEntry = new QLineEdit(this);
  fileBrowseBtn = new QPushButton("Browse", this);
  fileAddBtn = new QPushButton("Add", this);
  fileRmvBtn = new QPushButton("Rem", this);
  devicesComboBox = new QComboBox(this);
  map<int,string>::const_iterator iter;
  for(iter = outDevices.begin();iter!=outDevices.end();++iter){
    QString dev = QString::fromStdString(iter->second);
     devicesComboBox->addItem(dev);
  }
  connect(devicesComboBox,SIGNAL(currentIndexChanged(QString)),
          this,SLOT(on_devicesComboBox_IndexChanged(QString)));
  l->addWidget(fileEntry);
  l->addWidget(fileBrowseBtn);
  l->addWidget(fileAddBtn);
  l->addWidget(fileRmvBtn);
  l->addWidget(devicesComboBox);
  layout->addLayout(l);

  l = new QHBoxLayout();
  tm = new TimeLabel(this);
  tb = new TimeLabel(this);
  te = new TimeLabel(this);
  td = new TimeLabel(this);
  QLabel* spacer = new QLabel(this);
  spacer->setFixedHeight(0);
  spacer->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
  
  tm->setFrameStyle(QFrame::Box | QFrame::Sunken);
  tb->setFrameStyle(QFrame::Box | QFrame::Sunken);
  te->setFrameStyle(QFrame::Box | QFrame::Sunken);
  td->setFrameStyle(QFrame::Box | QFrame::Sunken);

  tm->setFixedSize(85,20);
  tb->setFixedSize(85,20);
  te->setFixedSize(85,20);
  td->setFixedSize(85,20);

  tm->setAlignment(Qt::AlignRight);
  tb->setAlignment(Qt::AlignRight);
  te->setAlignment(Qt::AlignRight);
  td->setAlignment(Qt::AlignRight);

  connect(selection, SIGNAL(waveformSelectionChanged(double,double,Waveform*)),
	  this, SLOT(changeSelection(double,double,Waveform*)));

  playBtn = new QPushButton(">", this);
  repeatBtn = new QPushButton("R", this);
  pauseBtn = new QPushButton("||", this);
  stopBtn = new QPushButton("X", this);

  speedSlider = new QSlider(this);
  speedSlider->setOrientation(Qt::Horizontal);
  speedSlider->setFixedWidth(60);
  speedSlider->setMinimum(-10);
  speedSlider->setMaximum(10);



  l->addWidget(tm);
  l->addWidget(tb);
  l->addWidget(te);
  l->addWidget(td);

  l->addWidget(spacer);

  l->addWidget(playBtn);
  l->addWidget(repeatBtn);
  l->addWidget(pauseBtn);
  l->addWidget(stopBtn);
  l->addWidget(speedSlider);
  layout->addLayout(l);

  connect(speedSlider, SIGNAL(valueChanged(int)),
	  this, SLOT(setSpeed(int)));

  playBtn->setFixedSize(20,20);
  repeatBtn->setFixedSize(20,20);
  pauseBtn->setFixedSize(20,20);
  stopBtn->setFixedSize(20,20);

  connect(playBtn, SIGNAL(clicked()), this, SLOT(play()));
  connect(repeatBtn, SIGNAL(clicked()), this, SLOT(repeat()));
  connect(pauseBtn, SIGNAL(clicked()), this, SLOT(pauseResume()));
  connect(stopBtn, SIGNAL(clicked()), this, SLOT(stop()));

  sb = new WaveformScrollBar(this);
  layout->addWidget(sb);

  player->getPlayerTicker()->registerReceiver(sb);
  player->getPlayerTicker()->registerReceiver(tm);
  player->getPlayerTicker()->registerReceiver(cursor);
  
  grid = new QGridLayout();
  grid->setSpacing(1);
  grid->addWidget(new QWidget(this), 0,0);
  ruler = new WaveformRuler(true, this);
  grid->addWidget(ruler,0,1);
  gridCurRow = 1;
  layout->addLayout(grid);


  connect(fileAddBtn, SIGNAL(clicked()), this, SLOT(addSndFile()));
  connect(fileRmvBtn, SIGNAL(clicked()), this, SLOT(removeSndFile()));

  connect(fileEntry, SIGNAL(returnPressed()), this, SLOT(addSndFile()));
  connect(fileBrowseBtn, SIGNAL(clicked()), this, SLOT(browseSndFile()));


  //addSndFile();
}

MyWidget::~MyWidget()
{
  for (size_t i=0; i<sndfiles.size(); ++i)
    delete sndfiles[i];
  player->terminatePlayer();
  delete player;
}

void MyWidget::addSndFile()
{
    if(fileEntry->text().isEmpty()){
        //fileEntry->setText("/Users/Admin/Documents/python/_testfiles/testfolder/_no_prob/_Time/Test_Time_St_16mono44.wav");
        fileEntry->setText("/Users/Admin/Documents/python/_testfiles/testfolder/_no_prob/_Time/Test_Time_St_16_00.wav");
    }

    QFileInfo finfo(fileEntry->text());
    if (!finfo.exists()) {
        QString msg("Can't find file: '%1'");
        QMessageBox::critical(this,"Error",msg.arg(finfo.filePath()));
        return;
    }
    player->pause();

    player->addFile(finfo.filePath().toStdString().c_str());
    double len = 10;
    soundfile = new SndFile(finfo.filePath().toStdString().c_str());
    len = soundfile->getLengthSeconds();
    soundfile->open();

    if(soundfile){
        for (int ch=0; ch<soundfile->getChannels(); ++ch, ++gridCurRow)
        {
            WaveformVRuler *r = new WaveformVRuler(this);
            Waveform* w = new Waveform  (soundfile, ch, 0.0, len, this); //4ter Parameter ist Duration

            //QSlider* mag = new QSlider(this);// Volume Slider
            QVBoxLayout* vbox = new QVBoxLayout();
            //QCheckBox* mutt = new QCheckBox(this);
            //QSlider* vol = new QSlider(this);
            //QLayoutIterator it = layout->iterator();

            grid->addWidget(r, gridCurRow, 0); // Vertical Ruler (WaveformRuler)
            grid->addWidget(w, gridCurRow, 1); // Waveform
            //grid->addWidget(mag, gridCurRow, 2); // Volume Slider

            grid->addLayout(vbox, gridCurRow, 3);

            //mag->show();
            //vbox->show();

            waveforms[sndfiles.size()][ch] = w;
            r->connectToWaveform(w);
            r->show();
            w->show();


            cursor->registerWaveform(w);
            selection->registerWaveform(w);

            connect(w, SIGNAL(waveformMouseMoved(Waveform*,double)),
                this, SLOT(setTime(Waveform*,double)));

            sb->registerWaveform(w);

            if (hasRuler == false) {
                ruler->connectToWaveform(w);
                ruler->show();
                hasRuler = true;
            }

            if (sndfiles.size()>=2)
            {
                cout << "++++++++++++++++++++++++++++++++++++++++++++NOT EMPTY" << endl;
                //player->closePlayer();
                //for (int ch=0; ch<soundfile->getChannels(); ++ch,++gridCurRow)
               {
                grid->removeWidget(r);
                grid->removeWidget(w);
                grid->removeItem(vbox);
                delete r;
                delete w;
                }
                //sndfiles.pop_back();
            }
            //QColor waveformColor(QColor(42, 38, 38));
            //QColor backgroundColor(QColor(85, 85, 127));
            //soundfile->setColor(waveformColor,backgroundColor);
            w->display(0,len,true);
        }// for
    }
  //player->resume();




   QSlider *hzoomSlider = new QSlider(this);
   hzoomSlider->setOrientation(Qt::Horizontal);
   hzoomSlider->setFixedWidth(300);
   hzoomSlider->setMinimum(-10);
   hzoomSlider->setMaximum(10);

   //grid->addWidget(hzoomSlider, 4,0);




   sndfiles.push_back(soundfile);


}

void MyWidget::removeSndFile()
{
    cout << "removeSoundfile Called" << endl;

    for (size_t i=0; i<sndfiles.size(); ++i)
    {

    }
        //  delete sndfiles[i];
    //player->removeSndFile();



    sndfiles.pop_back();
}


void MyWidget::browseSndFile()
{
  QString sname = QFileDialog::getOpenFileName(
          this,
          "Open Audio File",
              "/Users/Admin/Documents/python/_testfiles/testfolder/_no_prob/_Time",
          "All (*.*)"
          );
  if (sname.length() > 0)
    fileEntry->setText(sname.toUtf8());
  addSndFile();//hinzugefuegt - geaendert
}

void MyWidget::play()
{
  paused = false;
  pauseBtn->setText("||");
  player->play(0,5);
  //if (selection->getWidthSeconds() < 0.90){
      //player->play(selection->getBeginSeconds(),
      //   (soundfile->getLengthSeconds() - selection->getBeginSeconds()));}
  //else if (selection->getWidthSeconds() ==0 && selection->getWidthSeconds()==0)
  //      player->play(0,soundfile->getLengthSeconds());
  //else{
  //player->play(selection->getBeginSeconds(),
    //       selection->getWidthSeconds());
//}


}

void MyWidget::repeat()
{
  paused = false;
  pauseBtn->setText("||");
  //player->repeat(selection->getBeginSeconds(),
    //	 selection->getWidthSeconds());
}

void MyWidget::pauseResume()
{
  if (paused) {
    paused = false;
    player->resume();
    pauseBtn->setText("||");
  }
  else {
    paused = true;
    player->pause();
    pauseBtn->setText("=");
  }
}

void MyWidget::stop()
{
  paused = false;
  pauseBtn->setText("||");
  player->stop();
}

void MyWidget::changeSelection(double beg, double dur, Waveform*)
{
  tb->setTime(beg);
  te->setTime(beg+dur);
  td->setTime(dur);
}

void MyWidget::setSpeed(int v)
{
  player->setSpeed(pow(2.0,v/10.0));
}

void MyWidget::setTime(Waveform*,double t)
{
  tm->setTime(t);
}

void MyWidget::on_devicesComboBox_IndexChanged(QString id){
    int _id;
    //! c++11
    /**
    for(auto iter: outDevices){
        if(iter.second == id.toStdString().c_str()){
        _id =  iter.first;
        }
    }
    */
    map<int,string>::iterator iter;
    for(iter = outDevices.begin();iter != outDevices.end();++iter) {

        //QString dev = QString::fromStdString(iter->second);
        // devicesComboBox->addItem(dev);
        if(iter->second == id.toStdString().c_str()){
        _id =  iter->first;
        }
    }
    player->setOutputDevice(_id);
}

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);
  
  MyWidget w;

  w.show();

  app.exec();
}
