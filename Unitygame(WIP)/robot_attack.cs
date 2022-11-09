using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class robot_attack : MonoBehaviour
{
    public bool robotisActive = true;




    // Start is called before the first frame update
    void Start()
    {
        robotisActive = true;
        InitRobot();
    }

    // Update is called once per frame
    void Update()
    {

        if (!robotisActive)
        {
            return;
        }
        else
        {
            Animator animator = GetComponent<Animator>();
            int random = animator.GetInteger("random");
            random = Random.Range(1, 3);
            animator.SetInteger("random", random);
        }

    }

    public void InitRobot()
    {
        Animator animator = GetComponent<Animator>();
        int random = animator.GetInteger("random");
        animator.SetInteger("random", 0);
    }
}
