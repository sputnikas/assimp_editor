# Assimp explorer

Программа для анализа содержимого 3d моделей на основе библиотеки assimp.
Использование:
```
assimpExplorer [input_filename]
```
Поддерживаемые форматы файлов:
```
*.3d;*.3ds;*.3mf;*.ac;*.ac3d;*.acc;*.amf;*.ase;*.ask;*.assbin;*.b3d;*.blend;*.bsp;*.bvh;*.cob;*.csm;*.dae;*.dxf;*.enff;*.fbx;*.glb;*.gltf;*.hmp;*.ifc;*.ifczip;*.iqm;*.irr;*.irrmesh;*.lwo;*.lws;*.lxo;*.md2;*.md3;*.md5anim;*.md5camera;*.md5mesh;*.mdc;*.mdl;*.mesh;*.mesh.xml;*.mot;*.ms3d;*.ndo;*.nff;*.obj;*.off;*.ogex;*.pk3;*.ply;*.pmx;*.prj;*.q3o;*.q3s;*.raw;*.scn;*.sib;*.smd;*.step;*.stl;*.stp;*.ter;*.uc;*.vrm;*.vta;*.x;*.x3d;*.x3db;*.xgl;*.xml;*.zae;*.zgl
```
Пример вывода информации в консоль:
```
Model ../data/Rigged Hand.fbx information:
-------------------------------------------------------------------------
Num of Meshes     = 2
Num of Animations = 6
Num of Cameras    = 0
Num of Lights     = 2
Num of Materials  = 1
Num of Textures   = 0
Num of Skeletons  = 0
-------------------------------------------------------------------------
Mesh 0 Info:
    Name  = Mesh
    Num of AnimMeshes      = 0
    Num of Bones           = 59
    Num of Faces           = 16576
    Num of UVComponents[0] = 2
    Num of UVComponents[1] = 0
    Num of UVComponents[2] = 0
    Num of UVComponents[3] = 0
    Num of UVComponents[4] = 0
    Num of UVComponents[5] = 0
    Num of UVComponents[6] = 0
    Num of UVComponents[7] = 0
    Num of Vertices        = 33152
    Num of Color Channels  = 0
    Num of UV Channels     = 1
    PrimitiveTypes  = 20
    Bounding box = (0.000000, 0.000000, 0.000000) -> (0.000000, 0.000000, 0.000000)
    Index of method of morphing = 0
    Has tangents and bitangents = 1
    Index of material = 0
-------------------------------------------------------------------------
Bones 0 information:
Num of Weights = 0
Name = ribs.001
-------------------------------------------------------------------------
...
-------------------------------------------------------------------------
Bones 57 information:
Num of Weights = 3888
Name = finger_pinky.03.R
-------------------------------------------------------------------------
Bones 58 information:
Num of Weights = 0
Name = forearm.R.003
-------------------------------------------------------------------------
Armature 0 information in adress 188fac5a940:
    Armature:
        ribs.001:
            shoulder.L:
                upper_arm.L:
                    forearm.L:
                        hand.L:
                            palm.02.L.001:
                                palm.02.L:
                                    finger_middle.01.L:
                                        finger_middle.02.L:
                                            finger_middle.03.L:
                                                finger_middle.03.L_end;
                            palm.03.L.001:
                                palm.03.L:
                                    finger_ring.01.L:
                                        finger_ring.02.L:
                                            finger_ring.03.L:
                                                finger_ring.03.L_end;
                            palm.04.L.001:
                                palm.04.L:
                                    finger_pinky.01.L:
                                        finger_pinky.02.L:
                                            finger_pinky.03.L:
                                                finger_pinky.03.L_end;
                            palm.01.L.001:
                                palm.01.L:
                                    finger_index.01.L:
                                        finger_index.02.L:
                                            finger_index.03.L:
                                                finger_index.03.L_end;
                                    thumb.01.L.001:
                                        thumb.01.L:
                                            thumb.02.L:
                                                thumb.03.L:
                                                    thumb.03.L_end;
                        forearm.L.003:
                            forearm.L.003_end;
            shoulder.R:
                upper_arm.R:
                    forearm.R:
                        hand.R:
                            palm.01.R.001:
                                palm.01.R:
                                    finger_index.01.R:
                                        finger_index.02.R:
                                            finger_index.03.R:
                                                finger_index.03.R_end;
                                    thumb.01.R.001:
                                        thumb.01.R:
                                            thumb.02.R:
                                                thumb.03.R:
                                                    thumb.03.R_end;
                            palm.02.R.001:
                                palm.02.R:
                                    finger_middle.01.R:
                                        finger_middle.02.R:
                                            finger_middle.03.R:
                                                finger_middle.03.R_end;
                            palm.03.R.001:
                                palm.03.R:
                                    finger_ring.01.R:
                                        finger_ring.02.R:
                                            finger_ring.03.R:
                                                finger_ring.03.R_end;
                            palm.04.R.001:
                                palm.04.R:
                                    finger_pinky.01.R:
                                        finger_pinky.02.R:
                                            finger_pinky.03.R:
                                                finger_pinky.03.R_end;
                        forearm.R.003:
                            forearm.R.003_end;
-------------------------------------------------------------------------
...
-------------------------------------------------------------------------
...
-------------------------------------------------------------------------
Animation 2 Info:
    Name  = Armature|00
    Num of NumChannels          = 60
    Num of NumMeshChannels      = 0
    Num of NumMorphMeshChannels = 0
    Duration                    = 1.000000
    TicksPerSecond              = 24.000000
    -------------------------------------------------------------------------
    2 Animation 0 Channel Info
    Name of affect node: mNodeName = Armature
    NumPositionKeys = 2
    NumRotationKeys = 2
    NumScalingKeys  = 2
    -------------------------------------------------------------------------
    2 Animation 1 Channel Info
    Name of affect node: mNodeName = finger_index.01.L
    NumPositionKeys = 2
    NumRotationKeys = 2
    NumScalingKeys  = 2
    -------------------------------------------------------------------------
    ...
-------------------------------------------------------------------------
...
-------------------------------------------------------------------------
Light 0 Info:
    Name  = Point
    Type     = 2 = POINT
    Position = (0.000000, 0.000000, 0.000000)
    AttenuationConstant  = 0.000000
    AttenuationLinear    = 0.000000
    AttenuationQuadratic = 0.003200
    ColorAmbient  = (0.000000, 0.000000, 0.000000)
    ColorDiffuse  = (1.000000, 1.000000, 1.000000)
    ColorSpecular = (1.000000, 1.000000, 1.000000)
-------------------------------------------------------------------------
...
-------------------------------------------------------------------------
Material 0 Info:
    Name  = Material.004
    Num of properties  = 35
    Num allocated  = 40
-------------------------------------------------------------------------
    Property 0 Info:
        Type of property         = aiPTI_String
        Name of property         = ?mat.name
        Data length buffer       = 17
        Index of texture         = 0
        Semantic of use texture  = 0
        Strange Data (Device Control Symbols in ASCII) = 12 0
        Data = "Material.004"
-------------------------------------------------------------------------
    Property 1 Info:
        Type of property         = aiPTI_Buffer
        Name of property         = $mat.shadingm
        Data length buffer       = 4
        Index of texture         = 0
        Semantic of use texture  = 0
        Data = 0x03000000
-------------------------------------------------------------------------
    Property 2 Info:
        Type of property         = aiPTI_Float
        Name of property         = $clr.diffuse
        Data length buffer       = 12
        Index of texture         = 0
        Semantic of use texture  = 0
        Data = { 0.569813, 0.450562, 0.382238 }
-------------------------------------------------------------------------
    Property 3 Info:
        Type of property         = aiPTI_Float
        Name of property         = $clr.emissive
        Data length buffer       = 12
        Index of texture         = 0
        Semantic of use texture  = 0
        Data = { 0.000000, 0.000000, 0.000000 }
-------------------------------------------------------------------------
    Property 4 Info:
        Type of property         = aiPTI_Float
        Name of property         = $clr.ambient
        Data length buffer       = 12
        Index of texture         = 0
        Semantic of use texture  = 0
        Data = { 0.000000, 0.000000, 0.000000 }
-------------------------------------------------------------------------
    Property 5 Info:
        Type of property         = aiPTI_Float
        Name of property         = $clr.specular
        Data length buffer       = 12
        Index of texture         = 0
        Semantic of use texture  = 0
        Data = { 0.343934, 0.321736, 0.237172 }
-------------------------------------------------------------------------
    Property 6 Info:
        Type of property         = aiPTI_Float
        Name of property         = $mat.shinpercent
        Data length buffer       = 4
        Index of texture         = 0
        Semantic of use texture  = 0
        Data = { 0.225490 }
-------------------------------------------------------------------------
    Property 7 Info:
        Type of property         = aiPTI_Float
        Name of property         = $mat.shininess
        Data length buffer       = 4
        Index of texture         = 0
        Semantic of use texture  = 0
        Data = { 2.352941 }
-------------------------------------------------------------------------
    Property 8 Info:
        Type of property         = aiPTI_Float
        Name of property         = $mat.roughnessFactor
        Data length buffer       = 4
        Index of texture         = 0
        Semantic of use texture  = 0
        Data = { 0.846607 }
-------------------------------------------------------------------------
    Property 9 Info:
        Type of property         = aiPTI_Float
        Name of property         = $clr.transparent
        Data length buffer       = 12
        Index of texture         = 0
        Semantic of use texture  = 0
        Data = { 0.000000, 0.000000, 0.000000 }
-------------------------------------------------------------------------
    Property 10 Info:
        Type of property         = aiPTI_Float
        Name of property         = $mat.transparencyfactor
        Data length buffer       = 4
        Index of texture         = 0
        Semantic of use texture  = 0
        Data = { 0.000000 }
-------------------------------------------------------------------------
    Property 11 Info:
        Type of property         = aiPTI_Float
        Name of property         = $mat.opacity
        Data length buffer       = 4
        Index of texture         = 0
        Semantic of use texture  = 0
        Data = { 1.000000 }
-------------------------------------------------------------------------
    Property 12 Info:
        Type of property         = aiPTI_Float
        Name of property         = $clr.reflective
        Data length buffer       = 12
        Index of texture         = 0
        Semantic of use texture  = 0
        Data = { 1.000000, 1.000000, 1.000000 }
-------------------------------------------------------------------------
    Property 13 Info:
        Type of property         = aiPTI_Float
        Name of property         = $mat.reflectivity
        Data length buffer       = 4
        Index of texture         = 0
        Semantic of use texture  = 0
        Data = { 0.000000 }
-------------------------------------------------------------------------
    Property 14 Info:
        Type of property         = aiPTI_Float
        Name of property         = $mat.bumpscaling
        Data length buffer       = 4
        Index of texture         = 0
        Semantic of use texture  = 0
        Data = { 1.000000 }
-------------------------------------------------------------------------
    Property 15 Info:
        Type of property         = aiPTI_Float
        Name of property         = $mat.displacementscaling
        Data length buffer       = 4
        Index of texture         = 0
        Semantic of use texture  = 0
        Data = { 1.000000 }
-------------------------------------------------------------------------
    Property 16 Info:
        Type of property         = aiPTI_Float
        Name of property         = $raw.Shininess
        Data length buffer       = 4
        Index of texture         = 0
        Semantic of use texture  = 0
        Data = { 2.352941 }
-------------------------------------------------------------------------
    Property 17 Info:
        Type of property         = aiPTI_String
        Name of property         = $raw.DiffuseColor|file
        Data length buffer       = 24
        Index of texture         = 0
        Semantic of use texture  = 18
        Strange Data (Device Control Symbols in ASCII) = 19 0
        Data = "textures\HAND_C.jpg"
-------------------------------------------------------------------------
    Property 18 Info:
        Type of property         = aiPTI_Float
        Name of property         = $raw.DiffuseColor|uvtrafo
        Data length buffer       = 20
        Index of texture         = 0
        Semantic of use texture  = 18
        Data = { 0.000000, 0.000000, 1.000000, 1.000000, 0.000000 }
-------------------------------------------------------------------------
    Property 19 Info:
        Type of property         = aiPTI_Integer
        Name of property         = $raw.DiffuseColor|uvwsrc
        Data length buffer       = 4
        Index of texture         = 0
        Semantic of use texture  = 18
        Data = { 0 }
-------------------------------------------------------------------------
    Property 20 Info:
        Type of property         = aiPTI_String
        Name of property         = $raw.NormalMap|file
        Data length buffer       = 25
        Index of texture         = 0
        Semantic of use texture  = 18
        Strange Data (Device Control Symbols in ASCII) = 20 0
        Data = "textures\HAND_N .jpg"
-------------------------------------------------------------------------
    Property 21 Info:
        Type of property         = aiPTI_Float
        Name of property         = $raw.NormalMap|uvtrafo
        Data length buffer       = 20
        Index of texture         = 0
        Semantic of use texture  = 18
        Data = { 0.000000, 0.000000, 1.000000, 1.000000, 0.000000 }
-------------------------------------------------------------------------
    Property 22 Info:
        Type of property         = aiPTI_Integer
        Name of property         = $raw.NormalMap|uvwsrc
        Data length buffer       = 4
        Index of texture         = 0
        Semantic of use texture  = 18
        Data = { 0 }
-------------------------------------------------------------------------
    Property 23 Info:
        Type of property         = aiPTI_String
        Name of property         = $raw.SpecularColor|file
        Data length buffer       = 24
        Index of texture         = 0
        Semantic of use texture  = 18
        Strange Data (Device Control Symbols in ASCII) = 19 0
        Data = "textures\HAND_S.jpg"
-------------------------------------------------------------------------
    Property 24 Info:
        Type of property         = aiPTI_Float
        Name of property         = $raw.SpecularColor|uvtrafo
        Data length buffer       = 20
        Index of texture         = 0
        Semantic of use texture  = 18
        Data = { 0.000000, 0.000000, 1.000000, 1.000000, 0.000000 }
-------------------------------------------------------------------------
    Property 25 Info:
        Type of property         = aiPTI_Integer
        Name of property         = $raw.SpecularColor|uvwsrc
        Data length buffer       = 4
        Index of texture         = 0
        Semantic of use texture  = 18
        Data = { 0 }
-------------------------------------------------------------------------
    Property 26 Info:
        Type of property         = aiPTI_String
        Name of property         = $tex.file
        Data length buffer       = 24
        Index of texture         = 0
        Semantic of use texture  = 1
        Strange Data (Device Control Symbols in ASCII) = 19 0
        Data = "textures\HAND_C.jpg"
-------------------------------------------------------------------------
    Property 27 Info:
        Type of property         = aiPTI_Float
        Name of property         = $tex.uvtrafo
        Data length buffer       = 20
        Index of texture         = 0
        Semantic of use texture  = 1
        Data = { 0.000000, 0.000000, 1.000000, 1.000000, 0.000000 }
-------------------------------------------------------------------------
    Property 28 Info:
        Type of property         = aiPTI_Integer
        Name of property         = $tex.uvwsrc
        Data length buffer       = 4
        Index of texture         = 0
        Semantic of use texture  = 1
        Data = { 0 }
-------------------------------------------------------------------------
    Property 29 Info:
        Type of property         = aiPTI_String
        Name of property         = $tex.file
        Data length buffer       = 24
        Index of texture         = 0
        Semantic of use texture  = 2
        Strange Data (Device Control Symbols in ASCII) = 19 0
        Data = "textures\HAND_S.jpg"
-------------------------------------------------------------------------
    Property 30 Info:
        Type of property         = aiPTI_Float
        Name of property         = $tex.uvtrafo
        Data length buffer       = 20
        Index of texture         = 0
        Semantic of use texture  = 2
        Data = { 0.000000, 0.000000, 1.000000, 1.000000, 0.000000 }
-------------------------------------------------------------------------
    Property 31 Info:
        Type of property         = aiPTI_Integer
        Name of property         = $tex.uvwsrc
        Data length buffer       = 4
        Index of texture         = 0
        Semantic of use texture  = 2
        Data = { 0 }
-------------------------------------------------------------------------
    Property 32 Info:
        Type of property         = aiPTI_String
        Name of property         = $tex.file
        Data length buffer       = 25
        Index of texture         = 0
        Semantic of use texture  = 6
        Strange Data (Device Control Symbols in ASCII) = 20 0
        Data = "textures\HAND_N .jpg"
-------------------------------------------------------------------------
    Property 33 Info:
        Type of property         = aiPTI_Float
        Name of property         = $tex.uvtrafo
        Data length buffer       = 20
        Index of texture         = 0
        Semantic of use texture  = 6
        Data = { 0.000000, 0.000000, 1.000000, 1.000000, 0.000000 }
-------------------------------------------------------------------------
    Property 34 Info:
        Type of property         = aiPTI_Integer
        Name of property         = $tex.uvwsrc
        Data length buffer       = 4
        Index of texture         = 0
        Semantic of use texture  = 6
        Data = { 0 }
```