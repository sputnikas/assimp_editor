# Assimp converter

Программа для конвертации файлов 3d моделей из одного формата в другой на основе библиотеки assimp. Содержит код assimpExplorer для отладки и контроля содержимого файлов. К сожалению по какой-то причине не поддерживает файлы сгенерированные tinygltf в проекте oss_parser - неправильно преобразовывает анимации данных файлов. Версия assimp 5.4.3.

Использование:
```
assimpConverter [input_filename] [export_type] [output_filename]
```
Импортируемые форматы файлов:
```
*.3d;*.3ds;*.3mf;*.ac;*.ac3d;*.acc;*.amf;*.ase;*.ask;*.assbin;*.b3d;*.blend;*.bsp;*.bvh;*.cob;*.csm;*.dae;*.dxf;*.enff;*.fbx;*.glb;*.gltf;*.hmp;*.ifc;*.ifczip;*.iqm;*.irr;*.irrmesh;*.lwo;*.lws;*.lxo;*.md2;*.md3;*.md5anim;*.md5camera;*.md5mesh;*.mdc;*.mdl;*.mesh;*.mesh.xml;*.mot;*.ms3d;*.ndo;*.nff;*.obj;*.off;*.ogex;*.pk3;*.ply;*.pmx;*.prj;*.q3o;*.q3s;*.raw;*.scn;*.sib;*.smd;*.step;*.stl;*.stp;*.ter;*.uc;*.vrm;*.vta;*.x;*.x3d;*.x3db;*.xgl;*.xml;*.zae;*.zgl
```
Экспортируемые форматы файлов:
```
Export type  0 extension =     dae id = collada
Export type  1 extension =       x id = x
Export type  2 extension =     stp id = stp
Export type  3 extension =     obj id = obj
Export type  4 extension =     obj id = objnomtl
Export type  5 extension =     stl id = stl
Export type  6 extension =     stl id = stlb
Export type  7 extension =     ply id = ply
Export type  8 extension =     ply id = plyb
Export type  9 extension =     3ds id = 3ds
Export type 10 extension =    gltf id = gltf2
Export type 11 extension =     glb id = glb2
Export type 12 extension =    gltf id = gltf
Export type 13 extension =     glb id = glb
Export type 14 extension =  assbin id = assbin
Export type 15 extension =  assxml id = assxml
Export type 16 extension =     x3d id = x3d
Export type 17 extension =     fbx id = fbx
Export type 18 extension =     fbx id = fbxa
Export type 19 extension =     3mf id = 3mf
Export type 20 extension =    pbrt id = pbrt
Export type 21 extension =    json id = assjson
```