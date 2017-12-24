function Component()
{
    gui.pageWidgetByObjectName("LicenseAgreementPage").entered.connect(changeLicenseLabels);
}

changeLicenseLabels = function()
{
    page = gui.pageWidgetByObjectName("LicenseAgreementPage");
    page.AcceptLicenseLabel.setText("Yes I do!");
    page.RejectLicenseLabel.setText("No I don't!");
}

Component.prototype.createOperationsForArchive = function(archive)
{
    // don't use the default operation
    // component.createOperationsForArchive(archive);

    // add an extract operation with a modified path
    component.addOperation("Extract", archive, "@TargetDir@/extractToAnotherPath_Color");
}
