using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class sight : MonoBehaviour
{

    private float x_sensitivity = 3f;
    private float y_sensitivity = 3f;
    public bool sightisActive = true;


    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if (!sightisActive)
        {
            return;
        }
        else
        {
            Look();
        }
    }
    void Look()
    {
        float x_mouse = Input.GetAxis("Mouse X");

        Vector3 newRotation1 = transform.localEulerAngles;
        newRotation1.y += x_mouse * x_sensitivity;
        //if(newRotation1.y > -180 && newRotation1.y < 180)
        {
            transform.localEulerAngles = newRotation1;
        }

        float y_mouse = Input.GetAxis("Mouse Y");

        Vector3 newRotation2 = transform.localEulerAngles;
        newRotation2.x -= y_mouse * y_sensitivity;
        //if (newRotation2.x > -45 && newRotation2.x < 45)
        {
            transform.localEulerAngles = newRotation2;
        }
    }
}
