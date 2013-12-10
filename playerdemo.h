#ifndef _PLAYERDEMO_H
#define _PLAYERDEMO_H
//#define __DONT_USE_PLAYER
#define __DONT_USE_WAVEFORM

#include <QObject>
#include <QWidget>
#ifndef __DONT_USE_PLAYER
#include <psndplayer.h>
#endif


#ifndef __DONT_USE_WAVEFORM

#include <Waveform.h>
#include <WaveformScrollBar.h>
#include <WaveformRuler.h>
#include <WaveformCursorProxy.h>
#include <WaveformSelectionProxy.h>
#include <waveformthread.h>
#include <WaveformVRuler.h>
#include <TimeLabel.h>
#include <SndFile.h>

using namespace QWave2;

#endif



//class QWidget;
class QVBoxLayout;
class QLineEdit;
class QPushButton;
class QComboBox;
class QGridLayout;
class QSlider;


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
#ifndef __DONT_USE_WAVEFORM
  void changeSelection(double beg, double dur, Waveform*);
#endif
  void setSpeed(int);

private slots:
 #ifndef __DONT_USE_WAVEFORM
  //using namespace QWave2;
  void setTime(Waveform*,double);
#endif
  void on_devicesComboBox_IndexChanged(QString id);
private:
  QVBoxLayout* layout;         // main layout
#ifndef __DONT_USE_PLAYER
  PSndPlayer* player;
#endif



  QLineEdit* fileEntry;
  QPushButton* fileBrowseBtn;
  QPushButton* fileAddBtn;
  QPushButton* fileRmvBtn;
  QComboBox* devicesComboBox;


  QGridLayout* grid;     // 4 columns to contain waveforms
  int gridCurRow;
#ifndef __DONT_USE_WAVEFORM
  //WaveFormThread *waveFormThread;
  SndFile* soundfile;
  WaveformRuler* ruler;
  WaveformScrollBar* sb;
  WaveformCursorProxy* cursor;
  WaveformSelectionProxy* selection;

  TimeLabel* tm;
  TimeLabel* tb;
  TimeLabel* te;
  TimeLabel* td;
  vector<SndFile*> sndfiles;
  map<int,map<int,Waveform*> > waveforms;
#endif

  QPushButton* playBtn;
  QPushButton* repeatBtn;
  QPushButton* pauseBtn;
  QPushButton* stopBtn;

  QSlider* speedSlider;

  bool paused;

  bool hasRuler;
#ifndef __DONT_USE_PLAYER

  map<int, string> outDevices;
#endif
};

#endif
