// Local Variables:
// compile-command:"csc /target:exe								\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll			\
//   /main:PracticalDelegateTest /out:PracticalDelegateTest.exe PracticalDelegateTest.cs \
//   && PracticalDelegateTest arg1 "arg2""
// End:
using System;

class Car {
	public Car() {
		speed = 0;
	}
	public int Speed {
		get {
			return speed;
		}
		set {
			Console.WriteLine("speed configured : {0}", value);
			if (speed != value) {
				OnSpeedChanged(speed, value);
				speed = value;
			}
		}
	}
	private int speed;

	// 1. Delegate �����ϱ�(SpeedChangeHandler ��� Ŭ������ ���������)
	public delegate void SpeedChangeHandler(int beforeSpeed, int afterSpeed);
	// 2. Delegate ��ü �����ϱ�(private �ʵ� + ���ٸ޼ҵ�)
	private SpeedChangeHandler speedChangeHandler;
	public void RegisterSpeedChangeHandler(SpeedChangeHandler handler) {
		speedChangeHandler += handler;
	}
	public void UnregisterSpeedChangeHandler(SpeedChangeHandler handler) {
		speedChangeHandler -= handler;
	}
	// 3. � ��Ȳ���� ȣ��Ǿ� Delegate�� ȣ���ϴ� �Լ� �����.
	public virtual void OnSpeedChanged(int beforeSpeed, int afterSpeed) {
		if (speedChangeHandler != null) {
			speedChangeHandler(beforeSpeed, afterSpeed);
		}
	}
}

class PracticalDelegateTest {
	// 4. �ڵ鷯 �����
	public static void LogSpeedChange(int beforeSpeed, int afterSpeed) {
		Console.WriteLine("speed change : {0} --> {1}", beforeSpeed, afterSpeed);
	}
	public static void Main() {
		Car tucson = new Car();

		tucson.Speed = 10;
		// 5. �ڵ鷯 ����ϱ�
		Car.SpeedChangeHandler handler = new Car.SpeedChangeHandler(LogSpeedChange);
		tucson.RegisterSpeedChangeHandler(handler);

		tucson.Speed = 20;
		tucson.Speed = 30;

		// 5.1 �ڵ鷯 ��� �����ϱ�
		tucson.UnregisterSpeedChangeHandler(handler);

		tucson.Speed = 40;
	}
}