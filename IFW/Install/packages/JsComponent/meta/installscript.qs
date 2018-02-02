function Component()
{
    installer.installationFinished.connect(this, Component.prototype.installationFinishedPageIsShown);
    installer.finishButtonClicked.connect(this, Component.prototype.installationFinished);

    component.loaded.connect(this,MessageBox);
}

Component.prototype.createOperations = function()
{
    component.createOperations();
}

Component.prototype.installationFinishedPageIsShown = function()
{
    try {
        if (installer.isInstaller() && installer.status == QInstaller.Success) {
            installer.addWizardPageItem( component, "ReadMeCheckBoxForm", QInstaller.InstallationFinished );
        }
    } catch(e) {
        console.log(e);
    }
}

Component.prototype.installationFinished = function()
{
    try {
        if (installer.isInstaller() && installer.status == QInstaller.Success) {
            var isReadMeCheckBoxChecked = component.userInterface( "ReadMeCheckBoxForm" ).readMeCheckBox.checked;
            if (isReadMeCheckBoxChecked) {
                QDesktopServices.openUrl("file:///" + installer.value("TargetDir") + "/README.txt");
            }
        }
    } catch(e) {
        console.log(e);
    }
}

MessageBox = function()
{
    var result = QMessageBox["information"]("Information", "Installer", "Js Component load Ok.<br>" +
        "This message box was created using JavaScript.", QMessageBox.Ok | QMessageBox.Cancel);
    /*
    if (result == QMessageBox.Ok) {
        installer.setValue("FinishedText", "<font color='red' size=3>The installer was quit.</font>");
        installer.setDefaultPageVisible(QInstaller.TargetDirectory, false);
        installer.setDefaultPageVisible(QInstaller.ReadyForInstallation, false);
        installer.setDefaultPageVisible(QInstaller.ComponentSelection, false);
        installer.setDefaultPageVisible(QInstaller.StartMenuSelection, false);
        installer.setDefaultPageVisible(QInstaller.PerformInstallation, false);
        installer.setDefaultPageVisible(QInstaller.LicenseCheck, false);
        gui.clickButton(buttons.NextButton);
    } else {
        installer.setValue("FinishedText", "<font color='green' size=3>The installer was not quit by JavaScript.</font>");
    }
    */
}
