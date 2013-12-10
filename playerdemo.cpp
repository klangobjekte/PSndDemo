#include "playerdemo.h"
#include <QApplication>
#include <QLabel>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QMessageBox>
#include <iostream>
using namespace std;

//#ifdef _MSC_VER
//#include <QWave2/SndPlayerDirectSound.h>
//#else

//#endif
//#include <cmath>
//#include <math.h>
#ifndef __DONT_USE_WAVEFORM
using namespace QWave2;
#endif



MyWidget::MyWidget()
  : QWidget(),

    #ifndef __DONT_USE_PLAYER
    player(new PSndPlayer),
    #endif
    #ifndef __DONT_USE_WAVEFORM
    cursor(new WaveformCursorProxy(this)),
    selection(new WaveformSelectionProxy(this)),
    soundfile(0),
    #endif
    paused(false),
    hasRuler(false)//Flag fuer zustand von Horizontal Ruler

{

#ifndef __DONT_USE_PLAYER
  player->initPlayer();
  player->enableTicker();
  outDevices = player->getOutputDevices();
#endif
  QHBoxLayout* hBoxLayout;
    layout= new QVBoxLayout();
  hBoxLayout = new QHBoxLayout();
  hBoxLayout->addWidget(new QLabel("Audio File:", this));
  fileEntry = new QLineEdit(this);
  fileBrowseBtn = new QPushButton("Browse", this);
  fileAddBtn = new QPushButton("Add", this);
  fileRmvBtn = new QPushButton("Rem", this);
  devicesComboBox = new QComboBox(this);

#ifndef __DONT_USE_PLAYER
  map<int,string>::const_iterator iter;
  for(iter = outDevices.begin();iter!=outDevices.end();++iter){
    QString dev = QString::fromStdString(iter->second);
     devicesComboBox->addItem(dev);
  }
  connect(devicesComboBox,SIGNAL(currentIndexChanged(QString)),
          this,SLOT(on_devicesComboBox_IndexChanged(QString)));
#endif
  hBoxLayout->addWidget(fileEntry);
  hBoxLayout->addWidget(fileBrowseBtn);
  hBoxLayout->addWidget(fileAddBtn);
  hBoxLayout->addWidget(fileRmvBtn);
  hBoxLayout->addWidget(devicesComboBox);


  #ifndef __DONT_USE_WAVEFORM
  tm = new TimeLabel(this);
  tb = new TimeLabel(this);
  te = new TimeLabel(this);
  td = new TimeLabel(this);

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


  hBoxLayout->addWidget(tm);
  hBoxLayout->addWidget(tb);
  hBoxLayout->addWidget(te);
  hBoxLayout->addWidget(td);
#endif
  QLabel* spacer = new QLabel(this);
  spacer->setFixedHeight(0);
  spacer->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
  




  playBtn = new QPushButton(">", this);
  repeatBtn = new QPushButton("R", this);
  pauseBtn = new QPushButton("||", this);
  stopBtn = new QPushButton("X", this);

  playBtn->setFixedSize(20,20);
  repeatBtn->setFixedSize(20,20);
  pauseBtn->setFixedSize(20,20);
  stopBtn->setFixedSize(20,20);

  speedSlider = new QSlider(this);
  speedSlider->setOrientation(Qt::Horizontal);
  speedSlider->setFixedWidth(60);
  speedSlider->setMinimum(-10);
  speedSlider->setMaximum(10);





  hBoxLayout->addWidget(spacer);

  hBoxLayout->addWidget(playBtn);
  hBoxLayout->addWidget(repeatBtn);
  hBoxLayout->addWidget(pauseBtn);
  hBoxLayout->addWidget(stopBtn);
  hBoxLayout->addWidget(speedSlider);
  layout->addLayout(hBoxLayout);

  connect(speedSlider, SIGNAL(valueChanged(int)),
	  this, SLOT(setSpeed(int)));



  connect(playBtn, SIGNAL(clicked()), this, SLOT(play()));
  connect(repeatBtn, SIGNAL(clicked()), this, SLOT(repeat()));
  connect(pauseBtn, SIGNAL(clicked()), this, SLOT(pauseResume()));
  connect(stopBtn, SIGNAL(clicked()), this, SLOT(stop()));
#ifndef __DONT_USE_WAVEFORM
  sb = new WaveformScrollBar(this);

  layout->addWidget(sb);

#endif


#ifndef  __DONT_USE_PLAYER
#ifndef __DONT_USE_WAVEFORM
 player->getPlayerTicker()->registerReceiver(sb);
 player->getPlayerTicker()->registerReceiver(tm);
  player->getPlayerTicker()->registerReceiver(cursor);
#endif

#endif
  grid = new QGridLayout();
  grid->setSpacing(1);
  grid->addWidget(new QWidget(this), 0,0);
  #ifndef __DONT_USE_WAVEFORM
  ruler = new WaveformRuler(true, this);
  grid->addWidget(ruler,0,1);
#endif
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
  #ifndef __DONT_USE_WAVEFORM
    for (size_t i=0; i<sndfiles.size(); ++i)
    delete sndfiles[i];
#endif
#ifndef __DONT_USE_PLAYER
  player->terminatePlayer();
  delete player;
#endif
}

void MyWidget::addSndFile()
{
    QFileInfo finfo(fileEntry->text());
#ifndef __DONT_USE_PLAYER
    if(fileEntry->text().isEmpty()){
        //fileEntry->setText("/Users/Admin/Documents/python/_testfiles/testfolder/_no_prob/_Time/Test_Time_St_16mono44.wav");
        fileEntry->setText("/Users/Admin/Documents/python/_testfiles/testfolder/_no_prob/_Time/Test_Time_St_16_00.wav");
    }


    if (!finfo.exists()) {
        QString msg("Can't find file: '%1'");
        QMessageBox::critical(this,"Error",msg.arg(finfo.filePath()));
        return;
    }

    player->pause();
#endif


    double len = 10;
#ifdef WIN32
#ifndef __DONT_USE_PLAYER
    player->addFile(finfo.filePath().toStdWString().c_str());
#endif
    #ifndef __DONT_USE_WAVEFORM
    soundfile = new SndFile(finfo.filePath().toStdWString().c_str());
#endif
#else

    player->addFile(finfo.filePath().toStdString().c_str());
    soundfile = new SndFile(finfo.filePath().toStdString().c_str());
#endif
    #ifndef __DONT_USE_WAVEFORM
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
   sndfiles.push_back(soundfile);

  //player->resume();




   QSlider *hzoomSlider = new QSlider(this);
   hzoomSlider->setOrientation(Qt::Horizontal);
   hzoomSlider->setFixedWidth(300);
   hzoomSlider->setMinimum(-10);
   hzoomSlider->setMaximum(10);

   //grid->addWidget(hzoomSlider, 4,0);
#endif






}

void MyWidget::removeSndFile()
{
    cout << "removeSoundfile Called" << endl;
#ifndef __DONT_USE_WAVEFORM
    for (size_t i=0; i<sndfiles.size(); ++i)
    {

    }
        //  delete sndfiles[i];
    //player->removeSndFile();



    sndfiles.pop_back();
#endif
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
#ifndef __DONT_USE_PLAYER
  player->play(0,5);
#endif
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
    #ifndef __DONT_USE_PLAYER
    player->resume();
#endif
    pauseBtn->setText("||");
  }
  else {
    paused = true;
    #ifndef __DONT_USE_PLAYER
    player->pause();
#endif
    pauseBtn->setText("=");
  }
}

void MyWidget::stop()
{
  paused = false;
  pauseBtn->setText("||");
#ifndef __DONT_USE_PLAYER
  player->stop();
#endif
}

#ifndef __DONT_USE_WAVEFORM
void MyWidget::changeSelection(double beg, double dur, Waveform*)
{
  tb->setTime(beg);
  te->setTime(beg+dur);
  td->setTime(dur);
}
#endif

void MyWidget::setSpeed(int v)
{
  #ifndef __DONT_USE_PLAYER
    player->setSpeed(pow(2.0,v/10.0));
#endif
}

#ifndef __DONT_USE_WAVEFORM
void MyWidget::setTime(Waveform*,double t)
{
  tm->setTime(t);
}
#endif

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
#ifndef __DONT_USE_PLAYER
    map<int,string>::iterator iter;
    for(iter = outDevices.begin();iter != outDevices.end();++iter) {

        //QString dev = QString::fromStdString(iter->second);
        // devicesComboBox->addItem(dev);
        if(iter->second == id.toStdString().c_str()){
        _id =  iter->first;
        }
    }

    player->setOutputDevice(_id);
#endif
}


