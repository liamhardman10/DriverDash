include("/home/lxmh/Projects/DriverDash/build/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/driverdash-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase;qtdeclarative")

qt6_deploy_qml_imports(TARGET driverdash PLUGINS_FOUND plugins_found)
qt6_deploy_runtime_dependencies(
    EXECUTABLE "/home/lxmh/Projects/DriverDash/build/driverdash"
    ADDITIONAL_MODULES ${plugins_found}
    GENERATE_QT_CONF
)