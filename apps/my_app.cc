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

void MyApp::update() { }

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
    cinder::gl::drawSolidCircle(cinder::vec2(getWindowCenter()), mRadius);
}

void MyApp::DrawPaddleOne() const {
    cinder::gl::color(1, 1, 1);
    cinder::gl::drawSolidRect(Rectf(getWindowWidth()/2-20.0f, getWindowHeight()/2-20.0f, getWindowWidth()/2+20.0f, getWindowHeight()/2+20.0f));
}

void MyApp::DrawPaddleTwo() const {
    cinder::gl::color(1, 1, 1);
    cinder::gl::drawSolidRect(Rectf(getWindowWidth()/2-20.0f, getWindowHeight()/2-20.0f, getWindowWidth()/2+20.0f, getWindowHeight()/2+20.0f));
}

void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp
