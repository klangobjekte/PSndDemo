#ifndef _qwave2_h_
#define _qwave2_h_

#include <QLineEdit>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QComboBox>
#include <Waveform.h>
#include <WaveformScrollBar.h>
#include <WaveformRuler.h>
#include <WaveformCursorProxy.h>
#include <WaveformSelectionProxy.h>
#include <waveformthread.h>
#include <TimeLabel.h>
#include <SndFile.h>
#include <psndplayer.h>
#include <vector>
#include <map>
using namespace QWave2;

class MyWidget: public QWidget //MyWidget erbt von QWidget
{
  Q_OBJECT

public:
  MyWidget();
  ~MyWidget();

public slots:  
  void addSndFile();
  void removeSndFile();
  void browseSndFile();
  void play();
  void repeat();
  void pauseResume();
  void stop();

  void changeSelection(double beg, double dur, Waveform*);
  void setSpeed(int);

private slots:
  void setTime(Waveform*,double);
  void on_devicesComboBox_IndexChanged(QString id);
private:
  QVBoxLayout* layout;         // main layout
  PSndPlayer* player;
  //WaveFormThread *waveFormThread;
  SndFile* soundfile;
  QLineEdit* fileEntry;
  QPushButton* fileBrowseBtn;
  QPushButton* fileAddBtn;
  QPushButton* fileRmvBtn;
  QComboBox* devicesComboBox;

  QGridLayout* grid;     // 4 columns to contain waveforms
  int gridCurRow;
  WaveformRuler* ruler;
  WaveformScrollBar* sb;
  WaveformCursorProxy* cursor;
  WaveformSelectionProxy* selection;

  TimeLabel* tm;
  TimeLabel* tb;
  TimeLabel* te;
  TimeLabel* td;

  QPushButton* playBtn;
  QPushButton* repeatBtn;
  QPushButton* pauseBtn;
  QPushButton* stopBtn;

  QSlider* speedSlider;

  bool paused;

  bool hasRuler;

  vector<SndFile*> sndfiles;
  map<int,map<int,Waveform*> > waveforms;
  map<int, string> outDevices;
};

#endif
