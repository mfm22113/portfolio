using StarterAssets;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class playercontrol : MonoBehaviour
{
    //private CharacterController controller;
    //public GameObject player;
    public bool playerisActive = true;

    // Start is called before the first frame update
    void Start()
    {
        //controller = GetComponent<CharacterController>();
        //Debug.Log("start");
    }

    // Update is called once per frame
    void Update()
    {
        if (!playerisActive)
        {
            return;
        }
        else
        {
            Dodge();
        }
    }
    void Dodge()
    {
        if (Input.GetKey("a") && Input.GetKey("w"))
        {
            transform.position = new Vector3(-1, 2, 1);

        }
        else if (Input.GetKey("a") && Input.GetKey("s"))
        {
            transform.position = new Vector3(-1, 0, 1);

        }
        else if (Input.GetKey("d") && Input.GetKey("w"))
        {
            transform.position = new Vector3(1, 2, 1);

        }
        else if (Input.GetKey("d") && Input.GetKey("s"))
        {
            transform.position = new Vector3(1, 0, 1);

        }
        else if (Input.GetKey("w"))
        {
            transform.position = new Vector3(0, 2, 1);
            //Debug.Log(1);
        }
        else if (Input.GetKey("a"))
        {
            transform.position = new Vector3(-1, 1, 1);
            //Debug.Log(2);

        }
        else if (Input.GetKey("s"))
        {
            transform.position = new Vector3(0, 0, 1);
            //Debug.Log(3);
        }
        else if (Input.GetKey("d"))
        {
            transform.position = new Vector3(1, 1, 1);
            //Debug.Log(4);
        }
        else
        {
            transform.position = new Vector3(0, 1, 1);
        }
    }
    public void InitPosition()
    {
        transform.position = new Vector3(0, 1, 1);
    }
}
