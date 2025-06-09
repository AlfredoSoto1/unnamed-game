/*******************************************************************
 * @file   App.hpp
 * @brief  Application class for managing the application lifecycle.
 *
 * @author Alfredo
 * @date   May 2025
 *******************************************************************/
#pragma once

#include <memory>
#include <string>

#include "IMonitor.hpp"
#include "Types.hpp"

namespace uranium::core {

  UR_ABSTRACT_CLASS IApp {  //: UR_IMPLEMENTS events::ApplicationListener {
  public:
    /**
     * @brief Constructor for the IApp class.
     *        Initializes necessary resources for running the application.
     */
    explicit IApp() noexcept;
    virtual ~IApp() noexcept = default;

    /**
     * @brief Exits the application.
     *        This method is called to gracefully shut down the application.
     */
    void exit() noexcept;

  protected:
    // Derived classes may need a reference to the engine or other resources
    // Placeholder for future engine reference if needed
    // std::shared_ptr<Engine> engine;

    // virtual void onInit() = 0;
    // virtual void onUpdate() = 0;
    // virtual void onShutdown() = 0;

    /**
     * @brief Provides the primary monitor.
     *
     * @return const IMonitor*
     */
    virtual const IMonitor* primaryMonitor() = 0;

    /**
     * @brief Changes all settings related to a monitor to the one being
     *        selected.
     *
     * @return const IMonitor*
     */
    virtual const IMonitor* selectMonitor(uint32_t selection) = 0;

  protected:
    std::unique_ptr<IMonitor> monitor;

  private:
    void init();
    void run();
    void shutdown();

    // /**
    //  * @brief Handles the application exit event.
    //  *        Triggered when the application is exiting.
    //  * @param event The ApplicationEvent associated with the exit action.
    //  */
    // virtual void onApplicationExit(events::ApplicationEvent & event);

    // /**
    //  * @brief Handles the application start event.
    //  *        Triggered when the application has started.
    //  * @param event The ApplicationEvent associated with the start action.
    //  */
    // virtual void onApplicationStart(events::ApplicationEvent & event);

    // /**
    //  * @brief Handles the application pause event.
    //  *        Triggered when the application is paused.
    //  * @param event The ApplicationEvent associated with the pause action.
    //  */
    // virtual void onApplicationPause(events::ApplicationEvent & event);

    // /**
    //  * @brief Handles the application resume event.
    //  *        Triggered when the application resumes from a paused state.
    //  * @param event The ApplicationEvent associated with the resume action.
    //  */
    // virtual void onApplicationResume(events::ApplicationEvent & event);

  private:
    bool is_running;
  };

  /**
   * @class App
   * @brief Main class representing the application lifecycle. This singleton
   *        manages initialization, main loop, event handling, and cleanup.
   */
  UR_SINGLETON_CLASS App {
  public:
    /**
     * @brief Deleted copy constructor for the App class.
     *        Prevents copying of the App instance to ensure that only one
     *        instance of App exists at any time.
     *
     * @note This is a singleton class, and copying it would violate the
     *       singleton design pattern.
     */
    App(const App&) = delete;
    App& operator=(const App&) = delete;

    /**
     * @brief Retrieves the singleton instance of the IApp class.
     *        This method ensures that only one instance of App exists
     *        throughout the application lifecycle.
     * @return A reference to the singleton IApp instance.
     */
    static IApp& get() { return *instance; }

    /**
     * @brief Sets the singleton instance of the IApp class.
     *
     * @param app
     */
    static void borrow(std::unique_ptr<IApp> app);

    /**
     * @brief Releases the singleton instance of the IApp class.
     *        This method releases the ownership of the App instance
     *        and returns a unique pointer to it.
     * @return std::unique_ptr<IApp>
     */
    static std::unique_ptr<IApp> release();

  private:
    App() = default;
    ~App() = default;

  private:
    static inline std::unique_ptr<IApp> instance = nullptr;
  };
}  // namespace uranium::core
