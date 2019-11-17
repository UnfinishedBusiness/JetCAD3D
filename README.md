JetCad3D
==========

This repository contains the source code of [JetCad3D][jetcad_website], parametric
2D/3D CAD & CAM written in C/C++ and Javascript.  Forked from [SolveSpace][sswebsite], parametric 2D/3D CAD

We changed the interface to look and feel more like our online cloud-based 2D CAD software plus added a JavaScript engine that can draw entities and render dialogs with user input. This will be used for plugins, Gcode post processors, and the addition of a CAM processing system. Our goal is to provide a CAM experience with features that parallel Fusion 360 or HSMWorks.

[jetcad_website]: http://jetcad.io/
[sswebsite]: http://solvespace.com/

Drawing Features
-----------------
- Parametric Drafting
- DXF Exporting
- DXF Importing
- Extrusions
- Revolving
- Lofting (Not yet available)
- Extrude along a path (Not yet available)
- Boolean Fillets & Chamfers (Not yet available)
- Exports 3D files for printing
- Exports PDF files with dimensions
- 3D Assembly

Additional Features
--------------------
- Javascript Engine - (Done & Stable, easy interface to add bindings to)
- Dialogs Class - (In development. Dialogs can be moved around. Currently have buttons, labels, text input boxes, and checkboxes. Todo are tabs and radio groups.)
- CAM Tools (Not started yet, will be build on top of JavaScript engine)