function Component()
{
    component.loaded.connect(this, addRegisterFileCheckBox);

    installer.installationFinished.connect(this, addOpenFileCheckBoxToFinishPage);
    installer.finishButtonClicked.connect(this, openRegisteredFileIfChecked);
    component.unusualFileType = generateUnusualFileType(5)
}

generateUnusualFileType = function(length)
{
    var randomString = "";
    var possible = "abcdefghijklmnopqrstuvwxyz0123456789";

    for (var i = 0; i < length; i++)
        randomString += possible.charAt(Math.floor(Math.random() * possible.length));
    return randomString;
}

// called as soon as the component was loaded
addRegisterFileCheckBox = function()
{
    // don't show when updating or uninstalling
    if (installer.isInstaller()) {
        installer.addWizardPageItem(component, "RegisterFileCheckBoxForm", QInstaller.TargetDirectory);
        component.userInterface("RegisterFileCheckBoxForm").RegisterFileCheckBox.text =
            component.userInterface("RegisterFileCheckBoxForm").RegisterFileCheckBox.text + component.unusualFileType;
    }
}

// here we are creating the operation chain which will be processed at the real installation part later
Component.prototype.createOperations = function()
{
    // call default implementation to actually install the registeredfile
    component.createOperations();

    var isRegisterFileChecked = component.userInterface("RegisterFileCheckBoxForm").RegisterFileCheckBox.checked;
    if (installer.value("os") === "win") {
        var iconId = 0;
        var notepadPath = installer.environmentVariable("SystemRoot") + "\\notepad.exe";
        component.addOperation("RegisterFileType",
                               component.unusualFileType,
                               notepadPath + " '%1'",
                               "QInstaller Framework example file type",
                               "text/plain",
                               notepadPath + "," + iconId,
                               "ProgId=QtProject.QtInstallerFramework." + component.unusualFileType);
    }
    component.fileWithRegisteredType = installer.value("TargetDir") + "/registeredfile." + component.unusualFileType
    component.addOperation("Move", "@TargetDir@/registeredfile", component.fileWithRegisteredType);
}

openRegisteredFileIfChecked = function()
{
    if (!component.installed)
        return;

    if (installer.value("os") == "win" && installer.isInstaller() && installer.status == QInstaller.Success) {
        var isOpenRegisteredFileChecked = component.userInterface("OpenFileCheckBoxForm").OpenRegisteredFileCheckBox.checked;
        if (isOpenRegisteredFileChecked) {
            QDesktopServices.openUrl("file:///" + component.fileWithRegisteredType);
        }
    }
}

addOpenFileCheckBoxToFinishPage = function()
{
    if (installer.isInstaller() && installer.status == QInstaller.Success) {
        installer.addWizardPageItem(component, "OpenFileCheckBoxForm", QInstaller.InstallationFinished);
        component.userInterface("OpenFileCheckBoxForm").OpenRegisteredFileCheckBox.text =
            component.userInterface("OpenFileCheckBoxForm").OpenRegisteredFileCheckBox.text + component.unusualFileType;
    }
}
