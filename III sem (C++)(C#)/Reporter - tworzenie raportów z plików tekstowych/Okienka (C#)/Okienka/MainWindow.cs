using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Diagnostics; //for processes

namespace Okienka
{
    public partial class MainWindow : Form
    {
        private Process P = new Process();
        private char alg; //d - tree, m - map
        public MainWindow()
        {
            InitializeComponent();
        }

        private void MainWindow_Load(object sender, EventArgs e)
        {
            rBtree.Checked = true;
            alg = 'd';
        }

        private void bRead_Click(object sender, EventArgs e)
        {
            oFD.ShowDialog();
            if (!oFD.CheckFileExists)
                lProgress.Text = "Reading file failed.";
            else
            {
                lProgress.Text = "Reading file succeed.";
            }
        }

        private void bWrite_Click(object sender, EventArgs e)
        {
            P.StartInfo.FileName = "subprocess.exe";
            if(!oFD.CheckFileExists||oFD.FileName=="")
            {
                lProgress.Text = "Choose your file.";
                return;
            }
            P.StartInfo.Arguments = "\""+oFD.FileName+"\"";
            P.StartInfo.Arguments += " " + alg.ToString();
            if (P.Start())
            {
                lProgress.Text = "Program get started...";
            }
            else
            {
                lProgress.Text = "Program has failed.";
                P.Kill();
                return;
            }
            P.Close();
            lProgress.Text = "Report has been created.";
        }
        private void rBtree_CheckedChanged(object sender, EventArgs e)
        {
            if(alg=='m')
            {
                rBmap.Checked = false;
                rBtree.Checked = true;
                alg = 'd';
            }
        }

        private void rBmap_CheckedChanged(object sender, EventArgs e)
        {
            if (alg == 'd')
            {
                rBmap.Checked = true;
                rBtree.Checked = false;
                alg = 'm';
            }
        }
    }
}
