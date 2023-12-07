/*
Nathaniel Francis S. Filoteo
GDENG03 XX22
MCO: Comprehensive Exam
*/

using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine;
using UnityEditor;

public class LevelTranslator : EditorWindow
{
    [MenuItem("File/GDENG03 Comprehensive Exam/Open IET File...")]
    private static void SelectFile()
    {
        string filePath = EditorUtility.OpenFilePanel("Load IET Scene", "", "iet");
        if (filePath.Length > 0) {
            OpenIETScene(filePath);
        }
    }

    private static void OpenIETScene(string file_path)
    {
        string[] ietObjectInfoLines;
        ietObjectInfoLines = File.ReadAllLines(file_path);

        string objectName = "";
        int objectType = 0;
        Vector3 position = Vector3.zero;
        Vector3 rotation = Vector3.zero;
        Vector3 scale = Vector3.one;
        bool isActive = false;

        bool hasPhysics = false;
        bool isStatic = false;
        bool isGravityOn = false;
        float mass = 0.0f;

        for (int i = 0; i < ietObjectInfoLines.Length; i++)
        {
            switch (i % 11)
            {
                case 0: {
                    objectName = ietObjectInfoLines[i];
                } break;

                case 1: {
                    string[] split = ietObjectInfoLines[i].Split(' ');
                    objectType = int.Parse(split[1]);
                } break;

                case 2: {
                    string[] split = ietObjectInfoLines[i].Split(' ');
                    position.x = float.Parse(split[1]);
                    position.y = float.Parse(split[2]);
                    position.z = float.Parse(split[3]);
                } break;

                case 3: {
                    string[] split = ietObjectInfoLines[i].Split(' ');
                    rotation.x = float.Parse(split[1]);
                    rotation.x *= Mathf.Rad2Deg;
                    rotation.y = float.Parse(split[2]);
                    rotation.y *= Mathf.Rad2Deg;
                    rotation.z = float.Parse(split[3]);
                    rotation.z *= Mathf.Rad2Deg;
                    } break;

                case 4: {
                    string[] split = ietObjectInfoLines[i].Split(' ');
                    scale.x = float.Parse(split[1]);
                    scale.y = float.Parse(split[2]);
                    scale.z = float.Parse(split[3]);
                    } break;

                case 5: {
                    string[] split = ietObjectInfoLines[i].Split(' ');
                    int flag = int.Parse(split[1]);
                    if (flag == 0) isActive = false;
                    else isActive = true;
                } break;

                case 6: {
                    string[] split = ietObjectInfoLines[i].Split(' ');
                    int flag = int.Parse(split[1]);
                    if (flag == 0) hasPhysics = false;
                    else hasPhysics = true;
                } break;

                case 8: {
                    string[] split = ietObjectInfoLines[i].Split(' ');
                    int flag = int.Parse(split[1]);
                    if (flag == 0) isStatic = false;
                    else isStatic = true;
                } break;

                case 9: {
                    string[] split = ietObjectInfoLines[i].Split(' ');
                    int flag = int.Parse(split[1]);
                    if (flag == 0) isGravityOn = false;
                    else isGravityOn = true;
                    } break;

                case 10: {
                    string[] split = ietObjectInfoLines[i].Split(' ');
                    mass = float.Parse(split[1]);

                    if (objectType == 1) {
                        GameObject cube = GameObject.CreatePrimitive(PrimitiveType.Cube);
                        cube.name = objectName;
                        cube.SetActive(isActive);
                        cube.transform.position = position;
                        cube.transform.rotation = Quaternion.Euler(rotation);
                        cube.transform.localScale = scale;

                        if (hasPhysics) {
                            cube.AddComponent<Rigidbody>();
                            Rigidbody component = cube.GetComponent<Rigidbody>();
                            component.mass = mass;
                            component.isKinematic = isStatic;
                            component.useGravity = isGravityOn;
                        }
                    }

                    else if (objectType == 2) {
                        GameObject plane = GameObject.CreatePrimitive(PrimitiveType.Plane);
                        plane.name = objectName;
                        plane.SetActive(isActive);
                        plane.transform.position = position;
                        plane.transform.rotation = Quaternion.Euler(rotation);

                        scale.x *= 0.1f;
                        scale.z *= 0.1f;
                        plane.transform.localScale = scale;

                        if (hasPhysics) {
                            plane.AddComponent<Rigidbody>();
                            Rigidbody component = plane.GetComponent<Rigidbody>();
                            component.mass = mass;
                            component.isKinematic = isStatic;
                            component.useGravity = isGravityOn;
                        }
                    }
                    
                } break;

                default: break;
            }
        }
    }
}