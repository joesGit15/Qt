function Component()
{
    var error = false;
    if (error) {
        installer.setValue("component_errors", installer.value("component_errors") + ";;;"
            + "Error in component: " + component.name);
    }
    installer.setValue("ComponentError", error);
}
