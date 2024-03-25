using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace DataGridViewDynamicComboBoxExample
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            // DataGridViewに列を追加するにゃー
            DataGridViewComboBoxColumn comboBoxColumn = new DataGridViewComboBoxColumn();
            comboBoxColumn.HeaderText = "選択肢";
            comboBoxColumn.Name = "comboBoxColumn";

            // データを追加するにゃー
            dataGridView1.Rows.Add("選択肢1", "選択肢2", "選択肢3");
            dataGridView1.Rows.Add("選択肢A", "選択肢B", "選択肢C");

            // 各行のプルダウンリストの選択肢を設定するにゃー
            for (int i = 0; i < dataGridView1.Rows.Count; i++)
            {
                DataGridViewComboBoxCell comboBoxCell = (DataGridViewComboBoxCell)dataGridView1.Rows[i].Cells["comboBoxColumn"];
                comboBoxCell.DataSource = GetOptionsForRow(i);
            }

            // DataGridViewに列を追加するにゃー
            dataGridView1.Columns.Add(comboBoxColumn);
        }

        // 行ごとの選択肢を取得するメソッドにゃー
        private List<string> GetOptionsForRow(int rowIndex)
        {
            // 例として、行のインデックスに応じて異なる選択肢を返すにゃー
            if (rowIndex % 2 == 0)
            {
                return new List<string>() { "選択肢1", "選択肢2", "選択肢3" };
            }
            else
            {
                return new List<string>() { "選択肢A", "選択肢B", "選択肢C" };
            }
        }
    }
}


using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace DynamicComboBoxOptionsExample
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            // DataGridViewに列を追加するにゃー
            DataGridViewComboBoxColumn comboBoxColumn = new DataGridViewComboBoxColumn();
            comboBoxColumn.HeaderText = "選択肢";
            comboBoxColumn.Name = "comboBoxColumn";

            // 初期選択肢を設定するにゃー
            List<string> initialOptions = new List<string>() { "選択肢1", "選択肢2", "選択肢3" };
            comboBoxColumn.DataSource = initialOptions;

            // DataGridViewに列を追加するにゃー
            dataGridView1.Columns.Add(comboBoxColumn);

            // データを追加するにゃー
            dataGridView1.Rows.Add();

            // ボタンクリック時のイベントハンドラを設定するにゃー
            buttonChangeOptions.Click += ButtonChangeOptions_Click;
        }

        // 選択肢を変更するボタンがクリックされたときの処理にゃー
        private void ButtonChangeOptions_Click(object sender, EventArgs e)
        {
            // 新しい選択肢を生成するにゃー（ここではランダムな選択肢を作成する例にゃー）
            List<string> newOptions = new List<string>() { "新しい選択肢A", "新しい選択肢B", "新しい選択肢C" };

            // DataGridViewのプルダウンリストの選択肢を更新するにゃー
            ((DataGridViewComboBoxColumn)dataGridView1.Columns["comboBoxColumn"]).DataSource = newOptions;
        }
    }
}

