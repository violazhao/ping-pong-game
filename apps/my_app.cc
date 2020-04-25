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
    /*mRadius = 25;
    gui = pretzel::PretzelGui::create("Puzzle settings");
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
    //DrawPaddleOne();
}

void MyApp::DrawBackground() const {
    cinder::gl::clear(Color(0, 0, 0));
}

void MyApp::DrawNet() const {
    cinder::gl::color(1, 1, 1);
    cinder::gl::drawLine(cinder::vec2(getWindowWidth()/2, getWindowHeight()), cinder::vec2(getWindowWidth()/2, 0));
}

void MyApp::DrawPaddleOne() const {
    cinder::gl::clear(cinder::Color(124, 2, 4));
    Rectf drawSolidRect(Rectf(50, 900, 50, 500));
}

void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp
