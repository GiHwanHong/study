// -*- mode:csharp -*-
// Local Variables:
// compile-command:"csc /target:winexe\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll\
//   /out:SimpleButton.exe SimpleButton.cs\
//   && SimpleButton"
// End:
using System;
using System.Diagnostics;
using System.Drawing;
using System.Windows.Forms;

class SimpleButton : Form
{
	SimpleButton()
	{
		this.Text = "�׽�Ʈ ������";
		this.BackColor = Color.DarkOrange;
		m_button = new Button();
		m_button.Text = "�� ��ư";
		m_button.BackColor = Color.Red;
		m_button.Parent = this;
		m_button.Location = new Point(100,50);
		m_button.Click += new EventHandler(ButtonClicked);
		m_button.KeyDown += new KeyEventHandler(ButtonKeyDowned);
	}
	void ButtonClicked(Object sender, EventArgs ea)
	{
		Console.WriteLine("��ư Ŭ��");
	}
	void ButtonKeyDowned(Object sender, KeyEventArgs ea)
	{
		Console.WriteLine("��ư Ű���� ����.");
	}
	protected Button m_button;

	public static void Main()
	{
		Application.Run(new SimpleButton());
	}
}
