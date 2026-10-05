include(cmake/CPM.cmake)

# Done as a function so that updates to variables like
# CMAKE_CXX_FLAGS don't propagate out to other
# targets
function(myproject_setup_dependencies)

  # For each dependency, see if it's
  # already been provided to us by a parent project

  if(NOT TARGET fmtlib::fmtlib)
    cpmaddpackage(
      NAME
      fmt
      GITHUB_REPOSITORY
      "fmtlib/fmt"
      GIT_TAG
      "12.1.0"
      SYSTEM
      YES)
  endif()

  if(NOT TARGET spdlog::spdlog)
    cpmaddpackage(
      NAME
      spdlog
      VERSION
      1.17.0
      GITHUB_REPOSITORY
      "gabime/spdlog"
      SYSTEM
      YES
      OPTIONS
      "SPDLOG_FMT_EXTERNAL ON")
  endif()

  if(NOT TARGET imgui::imgui)
    cpmaddpackage(
      NAME
      imgui
      GIT_TAG
      "v1.92.9"
      GITHUB_REPOSITORY
      "ocornut/imgui"
      SYSTEM
      YES)
  endif()

endfunction()
