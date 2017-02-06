using UnityEngine;
using System.Collections;

public abstract class ReceiverAbstract : MonoBehaviour {

	public abstract void Receive(string[] order);
}
