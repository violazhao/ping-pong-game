// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <pretzel/PretzelGui.h>


namespace myapp {

using cinder::app::KeyEvent;

MyApp::MyApp() { }

void MyApp::setup() {
    mRadius = 25;
    gui = pretzel::PretzelGui::create("Puzzle settings");
    gui->setSize(cinder::vec2(10, 10));
    gui->setPos(cinder::vec2(0, 0));
    gui->addSlider("Puzzle Size", &mRadius, 2, 100);
    gui->addSaveLoad();
    gui->loadSettings();
    ci::gl::enableAlphaBlending();
}

void MyApp::update() { }

void MyApp::draw() {
    cinder::gl::clear(cinder::Color(1, 1, 1));
    cinder::gl::drawSolidCircle(cinder::vec2(getWindowCenter()), mRadius);
    gui->draw();
}

void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp
