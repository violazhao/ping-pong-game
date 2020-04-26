// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <pretzel/PretzelGui.h>


namespace myapp {

    using cinder::Color;
    using cinder::ColorA;
    using cinder::Rectf;
    using cinder::TextBox;
    using cinder::app::KeyEvent;
    using namespace std;

MyApp::MyApp() { }

void MyApp::setup() {
    /*gui = pretzel::PretzelGui::create("Puzzle settings");
    gui->setSize(cinder::vec2(180, 150));
    gui->setPos(cinder::vec2(0, 0));
    gui->addSlider("Puzzle Size", &mRadius, 2, 100);
    gui->addSaveLoad();
    gui->loadSettings();
    ci::gl::enableAlphaBlending();*/
}

void MyApp::update() {
    UpdateBall();
}

void MyApp::draw() {
    /*cinder::gl::clear(cinder::Color(1, 1, 1));
    cinder::gl::drawSolidCircle(cinder::vec2(getWindowCenter()), mRadius);
    gui->draw();*/
    cinder::gl::clear();
    DrawBackground();
    DrawNet();
    DrawBall();
    DrawPaddleOne();
    DrawPaddleTwo();
}

void MyApp::DrawBackground() const {
    cinder::gl::clear(Color(0, 0, 0));
}

void MyApp::DrawNet() const {
    cinder::gl::color(1, 1, 1);
    cinder::gl::drawLine(cinder::vec2(getWindowWidth()/2, getWindowHeight()), cinder::vec2(getWindowWidth()/2, 0));
}

void MyApp::DrawBall() const {
    cinder::gl::color(1, 1, 1);
    cinder::gl::drawSolidCircle(cinder::vec2(ball_xpos, ball_ypos), mRadius);
}

void MyApp::DrawPaddleOne() const {
    cinder::gl::color(1, 1, 1);
    cinder::gl::drawSolidRect(Rectf(getWindowWidth()/1.06f-5, getWindowHeight()/2-30.0f, getWindowWidth()/1.06f+5, getWindowHeight()/2+30.0f));
}

void MyApp::DrawPaddleTwo() const {
    cinder::gl::color(1, 1, 1);
    cinder::gl::drawSolidRect(Rectf(getWindowWidth()/20.0f-5, getWindowHeight()/2-30.0f, getWindowWidth()/20.0f+5, getWindowHeight()/2+30.0f));
}

void MyApp::UpdateBall() {
    ball_xpos += ball_xdir * ball_speed;
    ball_ypos += ball_ydir * ball_speed;
    if (ball_xpos < 0) {
        ball_xpos = 0;
        ball_xdir = fabs(ball_xdir);
    }
    if (ball_xpos > getWindowWidth()) {
        ball_xpos = getWindowWidth();
        ball_xdir = -fabs(ball_xdir);
    }
    if (ball_ypos < 0) {
        ball_ypos = 0;
        ball_ydir = fabs(ball_ydir);
    }
    if (ball_ypos > getWindowHeight()) {
        ball_ypos = getWindowHeight();
        ball_ydir = -fabs(ball_ydir);
    }
}

void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp
