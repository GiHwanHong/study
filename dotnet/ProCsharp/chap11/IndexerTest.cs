// Local Variables:
// compile-command:"csc /target:exe								\
//   /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll	\
//   /main:IndexerTest /out:IndexerTest.exe IndexerTest.cs 	\
//   && IndexerTest arg1 "arg2""
// End:
using System;

public interface ICategoryKeyValueProvider
{
	string this[string aCategory, string aKey] { get; set; }
}
      
public class SomeContainer : ICategoryKeyValueProvider 
{
	// ICategoryKeyValueProvider �������̽��� �޼ҵ� ����
	public string this[string aCategory, string aKey] {
		get { return string.Format("ī�װ�:{0} Ű:{1} �� ��", aCategory, aKey); }
		set { Console.WriteLine(@"ī�װ�:{0} Ű:{1} �� ���� ""{2}""�� ����", aCategory, aKey, value); }
	}
	// �б� ���� �ε���
	public int this[int row, int col] {
		get { return row * 1000 + col; }
	}
	// ���ڿ��� ���ڷ� �޴� ����
	public int this[string rowColExpr] {
		get { return this[Convert.ToInt32(rowColExpr.Substring(1,2)),
						  Convert.ToInt32(rowColExpr.Substring(4,2))]; }
		set { Console.Write("{0}�� ���� {1}�� �����մϴ�.", rowColExpr, value); }
	}
}
      
class IndexerTest {
	public static void Main() {
		SomeContainer c = new SomeContainer();
		Console.WriteLine("c[18,17]={0}", c[18,17]);
		Console.WriteLine("c[\"1817\"]={0}", c["r18c17"]);
		c["r19c20"] = 1004;

		Console.WriteLine("���������-3������������ ��: {0}", c["���������", "3����������"]);
		c["�����ȸ��", "��������"] = "����";
	}
}