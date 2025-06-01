#pragma once

#include "uranium/core/App.hpp"

#include <stdexcept>

using namespace uranium::core;

IApp::IApp() noexcept {}

void IApp::exit() noexcept { is_running = false; }

void IApp::init() {
  // Initialization code here
}

void IApp::run() {
  // Main loop code here
}

void IApp::shutdown() {
  // Cleanup code here
}

void App::borrow(std::unique_ptr<IApp> app) {
  if (!instance) {
    instance = std::move(app);
  } else {
    throw std::runtime_error("App instance already exists.");
  }
}

std::unique_ptr<IApp> App::release() {
  if (!instance) {
    throw std::runtime_error("No App instance to free.");
  }
  return std::move(instance);
}
