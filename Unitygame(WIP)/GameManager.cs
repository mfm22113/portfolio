using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameManager : MonoBehaviour
{

    //[SerializeField]
    //PlayerController player = null;
    [SerializeField]
    Canvas gameStartCanvas;
    [SerializeField]
    Canvas gameOverCanvas;
    [SerializeField]
    private playercontrol player;
    [SerializeField]
    private GameObject robot;
    [SerializeField]
    private robot_attack robotreset;


    // Start is called before the first frame update
    void Start()
    {
        player.gameObject.SetActive(false);
        robot.gameObject.SetActive(false);
        // �^�C�g����ʂ�\��
        gameStartCanvas.gameObject.SetActive(true);
    }

    // Update is called once per frame
    void Update()
    {

    }
    public void GameStart()
    {
        // �^�C�g����ʂ�Q�[���I�[�o�[��ʂ��\��
        gameStartCanvas.gameObject.SetActive(false);
        gameOverCanvas.gameObject.SetActive(false);

        Cursor.lockState = CursorLockMode.Locked;
        Cursor.visible = false;

        //transform.position = new Vector3(5, 1, 1);
        player.gameObject.SetActive(true);
        robot.gameObject.SetActive(true);
        robot.GetComponent<robot_attack>().robotisActive = true;
    }

    public void GameOver()
    {
        // �Q�[���I�[�o�[��ʂ̕\��
        gameOverCanvas.gameObject.SetActive(true);
        player.InitPosition();
        robotreset.InitRobot();
        player.gameObject.SetActive(false);
        robot.GetComponent<robot_attack>().robotisActive = false;
        //robot.gameObject.SetActive(false);
        Cursor.lockState = CursorLockMode.None;
        Cursor.visible = true;

    }
    public void Retry()
    {
        gameOverCanvas.gameObject.SetActive(false);
        GameStart();
    }
}
