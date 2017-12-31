var ComponentSelectionPage = null;

var Dir = new function () {
    this.toNativeSparator = function (path) {
        if (systemInfo.productType === "windows")
            return path.replace(/\//g, '\\');
        return path;
    }
};

function Component() {
    qsTr("Use qsTr can translate.");
    if (installer.isInstaller()) {
        component.loaded.connect(this, Component.prototype.installerLoaded);
        ComponentSelectionPage = gui.pageById(QInstaller.ComponentSelection);

        installer.setDefaultPageVisible(QInstaller.TargetDirectory, false);
        installer.setDefaultPageVisible(QInstaller.ComponentSelection, false);
        installer.setDefaultPageVisible(QInstaller.LicenseCheck, false);
        if (systemInfo.productType === "windows")
            installer.setDefaultPageVisible(QInstaller.StartMenuSelection, false);
        installer.setDefaultPageVisible(QInstaller.ReadyForInstallation, false);
    }
}

/*
Dynamic${ObjectName}

To register a custom page, use the installer::addWizardPage() method and
the object name set in the UI file (for example, "MyPage").
Then call the Dynamic${ObjectName}Callback() function (for example, DynamicMyPageCallback()):

function Controller()
{
  installer.addWizardPage(component, "MyPage", QInstaller.TargetDirectory)
}

Controller.prototype.DynamicMyPageCallback()
{
  var page = gui.pageWidgetByObjectName("DynamicMyPage");
  page.myButton.click,
  page.myWidget.subWidget.setText("hello")
}
*/

Component.prototype.installerLoaded = function () {
if (installer.addWizardPage(component, "TargetWidget", QInstaller.TargetDirectory)) {
        var widget = gui.pageWidgetByObjectName("DynamicTargetWidget");
        if (widget != null) {
            widget.targetChooser.clicked.connect(this, Component.prototype.chooseTarget);
            widget.targetDirectory.textChanged.connect(this, Component.prototype.targetChanged);

            widget.windowTitle = "Installation Folder";
            widget.targetDirectory.text = Dir.toNativeSparator(installer.value("TargetDir"));
        }
    }

    if (installer.addWizardPage(component, "InstallationWidget", QInstaller.ComponentSelection)) {
        var widget = gui.pageWidgetByObjectName("DynamicInstallationWidget");
        if (widget != null) {
            widget.customInstall.toggled.connect(this, Component.prototype.customInstallToggled);
            widget.defaultInstall.toggled.connect(this, Component.prototype.defaultInstallToggled);
            widget.completeInstall.toggled.connect(this, Component.prototype.completeInstallToggled);

            widget.defaultInstall.checked = true;
            widget.windowTitle = "Select Installation Type";
        }

        if (installer.addWizardPage(component, "LicenseWidget", QInstaller.LicenseCheck)) {
            var widget = gui.pageWidgetByObjectName("DynamicLicenseWidget");
            if (widget != null) {
                widget.acceptLicense.toggled.connect(this, Component.prototype.checkAccepted);

                widget.complete = false;
                widget.declineLicense.checked = true;
                widget.windowTitle = "License Agreement";
            }
        }

        if (installer.addWizardPage(component, "ReadyToInstallWidget", QInstaller.ReadyForInstallation)) {
            var widget = gui.pageWidgetByObjectName("DynamicReadyToInstallWidget");
            if (widget != null) {
                widget.showDetails.checked = false;
                widget.windowTitle = "Ready to Install";
            }
            var page = gui.pageByObjectName("DynamicReadyToInstallWidget");
            if (page != null) {
                page.entered.connect(this, Component.prototype.readyToInstallWidgetEntered);
            }
        }
    }
}

Component.prototype.targetChanged = function (text) {
    var widget = gui.pageWidgetByObjectName("DynamicTargetWidget");
    if (widget != null) {
        if (text != "") {
            if (!installer.fileExists(text + "/components.xml")) {
                widget.complete = true;
                installer.setValue("TargetDir", text);
                return;
            }
        }
        widget.complete = false;
    }
}

Component.prototype.chooseTarget = function () {
    var widget = gui.pageWidgetByObjectName("DynamicTargetWidget");
    if (widget != null) {
        var newTarget = QFileDialog.getExistingDirectory("Choose your target directory.", widget
            .targetDirectory.text);
        if (newTarget != "")
            widget.targetDirectory.text = Dir.toNativeSparator(newTarget);
    }
}

Component.prototype.customInstallToggled = function (checked) {
    if (checked) {
        if (ComponentSelectionPage != null)
            ComponentSelectionPage.selectDefault();
        installer.setDefaultPageVisible(QInstaller.ComponentSelection, true);
    }
}

Component.prototype.defaultInstallToggled = function (checked) {
    if (checked) {
        if (ComponentSelectionPage != null)
            ComponentSelectionPage.selectDefault();
        installer.setDefaultPageVisible(QInstaller.ComponentSelection, false);
    }
}

Component.prototype.completeInstallToggled = function (checked) {
    if (checked) {
        if (ComponentSelectionPage != null)
            ComponentSelectionPage.selectAll();
        installer.setDefaultPageVisible(QInstaller.ComponentSelection, false);
    }
}

Component.prototype.checkAccepted = function (checked) {
    var widget = gui.pageWidgetByObjectName("DynamicLicenseWidget");
    if (widget != null)
        widget.complete = checked;
}

Component.prototype.readyToInstallWidgetEntered = function () {
    var widget = gui.pageWidgetByObjectName("DynamicReadyToInstallWidget");
    if (widget != null) {
        var html = "<b>Components to install:</b><ul>";
        var components = installer.components();
        for (i = 0; i < components.length; ++i) {
            if (components[i].installationRequested())
                html = html + "<li>" + components[i].displayName + "</li>"
        }
        html = html + "</ul>";
        widget.showDetailsBrowser.html = html;
    }
}
