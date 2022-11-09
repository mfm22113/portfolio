using System.Collections;
using System.Collections.Generic;
using UnityEditor.Callbacks;
using UnityEngine;

public class hit : MonoBehaviour
{

    [SerializeField]
    GameManager gameManager;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
    /*void OnCollisionEnter(Collision collision)
    {
        Debug.Log("Hit1");
    }*/

    void OnTriggerEnter(Collider other)
    {
        //Debug.Log("Hit2");
        /*if (other.gameObject.name == ("collider1") || other.gameObject.name == ("collider2") || other.gameObject.name == ("collider3") || other.gameObject.name == ("collider4"))
        {
            gameManager.GameOver();
        }*/
        if(other.gameObject.name == ("Sword1_FBX") || other.gameObject.name == ("Sword3_FBX"))
        {
            gameManager.GameOver();
        }

    }
}
