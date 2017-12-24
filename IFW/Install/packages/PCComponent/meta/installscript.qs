
// Skip all pages and go directly to finished page.
// (see also componenterror example)
function cancelInstaller(message)
{
    installer.setDefaultPageVisible(QInstaller.Introduction, false);
    installer.setDefaultPageVisible(QInstaller.TargetDirectory, false);
    installer.setDefaultPageVisible(QInstaller.ComponentSelection, false);
    installer.setDefaultPageVisible(QInstaller.ReadyForInstallation, false);
    installer.setDefaultPageVisible(QInstaller.StartMenuSelection, false);
    installer.setDefaultPageVisible(QInstaller.PerformInstallation, false);
    installer.setDefaultPageVisible(QInstaller.LicenseCheck, false);

    var abortText = "<font color='red'>" + message +"</font>";
    installer.setValue("FinishedText", abortText);
}

// Returns the major version number as int
//   string.split(".", 1) returns the string before the first '.',
//   parseInt() converts it to an int.
function majorVersion(str)
{
    return parseInt(str.split(".", 1));
}

function Component()
{
    //
    // Check whether OS is supported.
    //
    // For Windows and OS X we check the kernel version:
    //  - Require at least Windows Vista (winnt kernel version 6.0.x)
    //  - Require at least OS X 10.7 (Lion) (darwin kernel version 11.x)
    //
    // If the kernel version is older we move directly
    // to the final page & show an error.
    //
    // For Linux, we check the distribution and version, but only
    // show a warning if it does not match our preferred distribution.
    //

    // start installer with -v to see debug output
    console.log("OS: " + systemInfo.productType);
    console.log("Kernel: " + systemInfo.kernelType + "/" + systemInfo.kernelVersion);

    var validOs = false;

    if (systemInfo.kernelType === "winnt") {
        if (majorVersion(systemInfo.kernelVersion) >= 6)
            validOs = true;
    } else if (systemInfo.kernelType === "darwin") {
        if (majorVersion(systemInfo.kernelVersion) >= 11)
            validOs = true;
    } else {
        if (systemInfo.productType !== "opensuse"
                || systemInfo.productVersion !== "13.2") {
            QMessageBox["warning"]("os.warning", "Installer",
                                   "Note that the binaries are only tested on OpenSUSE 13.2.",
                                   QMessageBox.Ok);
        }
        validOs = true;
    }

    if (!validOs) {
        cancelInstaller("Installation on " + systemInfo.prettyProductName + " is not supported");
        return;
    }

    //
    // Hide/select packages based on architecture
    //
    // Marking a component as "Virtual" will hide it in the UI.
    // Marking a component with "Default" will check it.
    //
    console.log("CPU Architecture: " +  systemInfo.currentCpuArchitecture);

    /*
    installer.componentByName("root.i386").setValue("Virtual", "true");
    installer.componentByName("root.x86_64").setValue("Virtual", "true");

    if ( systemInfo.currentCpuArchitecture === "i386") {
        installer.componentByName("root.i386").setValue("Virtual", "false");
        installer.componentByName("root.i386").setValue("Default", "true");
    }
    if ( systemInfo.currentCpuArchitecture === "x86_64") {
        installer.componentByName("root.x86_64").setValue("Virtual", "false");
        installer.componentByName("root.x86_64").setValue("Default", "true");
    }
    */
}
