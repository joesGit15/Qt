## How to add CheckBox in Table

### QTableWidget

#### Add CheckBox In Table Header

1. subclass `QHeaderView`, implement `paintSection` and `mousePressEvent`. like file `checkboxheaderview.h`
2. this header can be used in `QTableWidget` and `QTableView`

#### Add CheckBox In Table Cell

In TableWidget has two ways to work it out.

1. use the `setItemWidget` in TableWidget.
2. use `setItemDelegate` in TableWidget

### QTableView

#### Add CheckBox In Table Header

Has the same way with TableWidget.

#### Add CheckBox In Table Cell

In the Table View, also has two ways to work it out.

1. subclass `QAbstractTableModel`, implement `flags` and `data` function, like `tablemodel.h` 

---

