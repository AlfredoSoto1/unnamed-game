/*******************************************************************
 * @file   AppEntry.hpp
 * @brief  Application entry point functions.
 *
 * @author Alfredo
 * @date   May 2025
 *********************************************************************/
#pragma once

#include <string>
#include <vector>

#include "App.hpp"
#include "Types.hpp"
#include "Utils.hpp"

namespace uranium::core {
  /**
   * @namespace AppEntry
   * @brief Namespace for application entry point functions.
   *        Contains functions to create and manage the application entry point.
   */
  extern std::unique_ptr<IApp> launchApp(std::vector<std::string>& args);
}  // namespace uranium::core

int main(int argc, char** argv) {
  // Capture the command line arguments
  std::vector<std::string> args;
  for (int i = 0; i < argc; ++i) {
    args.emplace_back(argv[i]);
  }

  // Launch the application using the Uranium core library
  auto app = uranium::core::launchApp(args);

  if (!app) {
    // If the application failed to launch, print an error message
    std::cerr << "Failed to launch the application." << std::endl;
    return 1;
  }

  // Set the application instance in the App singleton
  uranium::core::App::borrow(std::move(app));

  // Run the application

  // Claim back the application instance and let the default destructor handle
  // cleanup
  uranium::core::App::release();

  return 0;  // Exit success
}
