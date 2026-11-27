find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(wt CONFIG REQUIRED)
find_package(Boost REQUIRED)
find_package(unofficial-sodium CONFIG REQUIRED)

find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

# Headless core library
add_library(tb-core-lib STATIC
	# Database
	"core/db/DatabaseWorker.cpp"
	
	"core/db/GenericSession.cpp"
	"core/db/SecuritySession.cpp"
	"core/db/UserSession.cpp"

	"core/db/repo/AuthRepository.cpp"

)

target_include_directories(tb-core-lib PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_compile_features(tb-core-lib PUBLIC cxx_std_20)
target_compile_definitions(tb-core-lib PUBLIC
	$<$<CONFIG:Debug>:TRX_DEVELOPER_BUILD>
)

target_link_libraries(
	tb-core-lib
	PUBLIC
	fmt::fmt
	spdlog::spdlog
	nlohmann_json::nlohmann_json
	Wt::Wt
	Wt::Dbo
	Wt::DboSqlite3
	Boost::headers
	unofficial-sodium::sodium
)

# Application executable
add_executable(
	tb-app
	# Entry Point
	"main.cpp"
)

set_target_properties(tb-app PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_link_libraries(
	tb-app
	PRIVATE
	tb-core-lib
	glfw
	OpenGL::GL
	imgui::imgui
)