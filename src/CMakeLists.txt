# Add source to this project's executable.
add_executable (
	TinyBudget
	"main.cpp"

	"tb/core/Application.cpp"
	"tb/app/modules/Session.cpp"
	
	"tb/app/ui/Controller.cpp"
	"tb/app/ui/AuthenticationForm.cpp"
	"tb/app/ui/MenuBar.cpp"
	"tb/app/ui/FinancialBookSetup.cpp"

	"tb/app/api/local/LocalApiService.cpp"
	"tb/app/api/local/LocalAuthClient.cpp"

	"tb/tools/Security.cpp"
)

set_target_properties(TinyBudget PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET TinyBudget PROPERTY CXX_STANDARD 20)
endif()

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
   	add_compile_definitions(TRX_DEVELOPER_BUILD)
endif()

find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(wt CONFIG REQUIRED)
find_package(Boost REQUIRED)
find_package(unofficial-sodium CONFIG REQUIRED)

target_link_libraries(
	TinyBudget
	PRIVATE
	fmt::fmt
	spdlog::spdlog
	glfw
	opengl32
	imgui::imgui
	nlohmann_json::nlohmann_json
	Wt::Wt
	Wt::Dbo
	Wt::DboSqlite3
	Boost::headers
	unofficial-sodium::sodium
)