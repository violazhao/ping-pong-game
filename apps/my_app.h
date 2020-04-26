// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <pretzel/PretzelGui.h>


namespace myapp {

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;

private:
    void DrawBackground() const;
    void DrawNet() const;
    void DrawBall() const;
    void DrawPaddleOne() const;
    void DrawPaddleTwo() const;
    void UpdateBall();

private:
    float mRadius = 10;
    float ball_xpos = getWindowWidth()/2;
    float ball_ypos = getWindowHeight()/2;
    float ball_xdir = -1.0f;
    float ball_ydir = 1.0f;
    int ball_speed = 8;
    pretzel::PretzelGuiRef gui;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
