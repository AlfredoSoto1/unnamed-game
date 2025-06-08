/*******************************************************************
 * @file   IMonitor.hpp
 * @brief  Interface for monitor-related functionality.
 *
 * @author Alfredo
 * @date   May 2025
 *******************************************************************/
#pragma once

#include <memory>
#include <vector>

#include "Types.hpp"

namespace uranium::core {

  class MonitorFactory final {
  public:
    /**
     * @brief Creates a monitor instance based on the selection criteria.
     *
     * @param selection The selection criteria for the monitor.
     * @return std::unique_ptr<IMonitor> A unique pointer to the created
     * monitor.
     */
    static std::unique_ptr<IMonitor> findMonitor(IMonitor::Selection selection);

    /**
     * @brief Retrieves a list of available monitors on the system.
     *
     * @return std::vector<std::unique_ptr<IMonitor>> A vector of unique
     *         pointers to the available monitors.
     */
    static std::vector<std::unique_ptr<IMonitor>> getMonitors();
  };

  UR_ABSTRACT_CLASS IMonitor final {
  public:
    enum class Selection {
      PRIMARY,
      ANY,
    };

  public:
    /**
     * @brief Checks if the monitor is connected.
     *
     * @return true if the monitor is connected, false otherwise.
     */
    bool isConnected() const;

    /**
     * @brief Get the Refreshrate object
     *
     * @return uint32_t
     */
    uint32_t getRefreshrate() const;

    /**
     * @brief Get the Resolution object
     *
     * @param width
     * @param height
     */
    void getResolution(uint32_t* width, uint32_t* height) const;

  private:
    explicit IMonitor() noexcept = default;
    virtual ~IMonitor() noexcept = default;
  };

}  // namespace uranium::core