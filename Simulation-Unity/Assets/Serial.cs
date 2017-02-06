using UnityEngine;
using System.IO.Ports;
using UnityEngine.UI;
using System.Collections.Generic;
using System;
using System.Collections;

public class Serial : MonoBehaviour
{

  [SerializeField]
  private Dropdown serialPicker;
  [SerializeField]
  private int baudRate = 115200;
  [SerializeField]
  private AX12Manager ax12Manager;

  SerialPort serialPort;
  List<string> portsNames;
  private string currentPortSelected;
  Coroutine coroutine;

  // Use this for initialization
  void Start()
  {
    portsNames = new List<string>();
    string[] ports = SerialPort.GetPortNames();
    portsNames.Clear();
    foreach (string s in ports)
    {
      portsNames.Add(s);
    }
    serialPicker.AddOptions(portsNames);
    serialPicker.onValueChanged.AddListener(OnClickSerialName);
  }

  public void OnClickSerialName(int value)
  {
    if (serialPicker.value == 0)
      return;
    Debug.Log("Selected Serial: " + portsNames[value - 1]);
    currentPortSelected = portsNames[value - 1];
    if (serialPort != null)
    {
      serialPort.Close();
    }
    serialPort = new SerialPort(currentPortSelected, baudRate, Parity.None, 8, StopBits.One);
    serialPort.ReadTimeout = 50; // in ms
    serialPort.NewLine = "\r"; //La stm32 attend un '\r' en fin de ligne, et non un "\r\n"
    try
    {
      serialPort.Open();
      if (coroutine != null)
        StopCoroutine(coroutine);

      coroutine = StartCoroutine(listenPort());
    }
    catch (Exception e)
    {
      Debug.Log(e);
    }

  }

  private IEnumerator listenPort()
  {
    string[] received = new string[0];
    while (true)
    {
      try
      {
        //serialPort.WriteLine("test");
        string read = serialPort.ReadLine();
        Debug.Log(read);
        received = read.Split(' ');
        if (received.Length > 2)
          forward(received);
      }
      catch (Exception e)
      {
        Debug.Log(e);
      }

      yield return new WaitForSeconds(0.2f);
    }
  }

  private void forward(string[] received)
  {
    if (received[0].CompareTo("AX12") == 0)
			ax12Manager.Receive(received);
  }

  void printf(string s)
  {
    serialPort.WriteLine(s);
  }

  void OnApplicationQuit()
  {
    if (serialPort != null)
    {
      serialPort.Close();
    }
  }
}