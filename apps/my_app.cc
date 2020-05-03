// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <pretzel/PretzelGui.h>
#include <mylibrary/player.h>

namespace myapp {

using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;
using cinder::TextBox;
using cinder::app::KeyEvent;
using mylibrary::Direction;
using namespace std;

const char kDbPath[] = "app.db";

MyApp::MyApp()
    : leaderboard_{cinder::app::getAssetPath(kDbPath).string()} {}

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
    cinder::gl::drawSolidCircle(cinder::vec2(ball_xpos, ball_ypos), ball_radius);
}

void MyApp::DrawPaddleOne() const {
    cinder::gl::color(1, 1, 1);
    cinder::gl::drawSolidRect(Rectf(paddle1_x1, paddle1_y1, paddle1_x2, paddle1_y2));
}

void MyApp::DrawPaddleTwo() const {
    cinder::gl::color(1, 1, 1);
    cinder::gl::drawSolidRect(Rectf(paddle2_x1, paddle2_y1, paddle2_x2, paddle2_y2));
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
    if (ball_xpos > paddle1_x1 && ball_ypos > paddle1_y1 && ball_xpos > paddle1_x2 && ball_ypos < paddle1_y2) {
        ball_xdir = -fabs(ball_xdir);
    }
    if (ball_xpos < paddle2_x1 && ball_ypos > paddle2_y1 && ball_xpos < paddle2_x2 && ball_ypos < paddle2_y2) {
        ball_xdir = fabs(ball_xdir);
    }
}

void MyApp::keyDown(KeyEvent event) {
    switch (event.getCode()) {
        case KeyEvent::KEY_UP:
        case KeyEvent::KEY_k:
        case KeyEvent::KEY_w: {
            paddle1_y1 = paddle1_y1 - 30;
            paddle1_y2 = paddle1_y2 - 30;
            break;
        }
        case KeyEvent::KEY_DOWN:
        case KeyEvent::KEY_j:
        case KeyEvent::KEY_s: {
            paddle1_y1 = paddle1_y1 + 30;
            paddle1_y2 = paddle1_y2 + 30;
            break;
        }
    }
}

}  // namespace myapp
