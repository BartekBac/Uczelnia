namespace Okienka
{
    partial class MainWindow
    {
        /// <summary>
        /// Wymagana zmienna projektanta.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Wyczyść wszystkie używane zasoby.
        /// </summary>
        /// <param name="disposing">prawda, jeżeli zarządzane zasoby powinny zostać zlikwidowane; Fałsz w przeciwnym wypadku.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Kod generowany przez Projektanta formularzy systemu Windows

        /// <summary>
        /// Metoda wymagana do obsługi projektanta — nie należy modyfikować
        /// jej zawartości w edytorze kodu.
        /// </summary>
        private void InitializeComponent()
        {
            this.bRead = new System.Windows.Forms.Button();
            this.bWrite = new System.Windows.Forms.Button();
            this.lProgress = new System.Windows.Forms.Label();
            this.oFD = new System.Windows.Forms.OpenFileDialog();
            this.gB = new System.Windows.Forms.GroupBox();
            this.rBmap = new System.Windows.Forms.RadioButton();
            this.rBtree = new System.Windows.Forms.RadioButton();
            this.gB.SuspendLayout();
            this.SuspendLayout();
            // 
            // bRead
            // 
            this.bRead.Location = new System.Drawing.Point(12, 12);
            this.bRead.Name = "bRead";
            this.bRead.Size = new System.Drawing.Size(75, 23);
            this.bRead.TabIndex = 0;
            this.bRead.Text = "Open";
            this.bRead.UseVisualStyleBackColor = true;
            this.bRead.Click += new System.EventHandler(this.bRead_Click);
            // 
            // bWrite
            // 
            this.bWrite.Location = new System.Drawing.Point(127, 12);
            this.bWrite.Name = "bWrite";
            this.bWrite.Size = new System.Drawing.Size(75, 23);
            this.bWrite.TabIndex = 1;
            this.bWrite.Text = "Create";
            this.bWrite.UseVisualStyleBackColor = true;
            this.bWrite.Click += new System.EventHandler(this.bWrite_Click);
            // 
            // lProgress
            // 
            this.lProgress.AutoSize = true;
            this.lProgress.Location = new System.Drawing.Point(9, 55);
            this.lProgress.Name = "lProgress";
            this.lProgress.Size = new System.Drawing.Size(174, 13);
            this.lProgress.TabIndex = 2;
            this.lProgress.Text = "Welcom to the \"Reporter\" program.";
            // 
            // oFD
            // 
            this.oFD.Filter = "Text files|*.txt";
            // 
            // gB
            // 
            this.gB.Controls.Add(this.rBmap);
            this.gB.Controls.Add(this.rBtree);
            this.gB.Location = new System.Drawing.Point(12, 89);
            this.gB.Name = "gB";
            this.gB.Size = new System.Drawing.Size(155, 77);
            this.gB.TabIndex = 3;
            this.gB.TabStop = false;
            this.gB.Text = "Choose algorithm:";
            // 
            // rBmap
            // 
            this.rBmap.AutoSize = true;
            this.rBmap.Location = new System.Drawing.Point(17, 50);
            this.rBmap.Name = "rBmap";
            this.rBmap.Size = new System.Drawing.Size(75, 17);
            this.rBmap.TabIndex = 1;
            this.rBmap.TabStop = true;
            this.rBmap.Text = "Map (STL)";
            this.rBmap.UseVisualStyleBackColor = true;
            this.rBmap.CheckedChanged += new System.EventHandler(this.rBmap_CheckedChanged);
            // 
            // rBtree
            // 
            this.rBtree.AutoSize = true;
            this.rBtree.Location = new System.Drawing.Point(16, 24);
            this.rBtree.Name = "rBtree";
            this.rBtree.Size = new System.Drawing.Size(79, 17);
            this.rBtree.TabIndex = 0;
            this.rBtree.TabStop = true;
            this.rBtree.Text = "Binary-Tree";
            this.rBtree.UseVisualStyleBackColor = true;
            this.rBtree.CheckedChanged += new System.EventHandler(this.rBtree_CheckedChanged);
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(216, 179);
            this.Controls.Add(this.gB);
            this.Controls.Add(this.lProgress);
            this.Controls.Add(this.bWrite);
            this.Controls.Add(this.bRead);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "MainWindow";
            this.Text = "Raporter";
            this.Load += new System.EventHandler(this.MainWindow_Load);
            this.gB.ResumeLayout(false);
            this.gB.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button bRead;
        private System.Windows.Forms.Button bWrite;
        private System.Windows.Forms.Label lProgress;
        private System.Windows.Forms.OpenFileDialog oFD;
        private System.Windows.Forms.GroupBox gB;
        private System.Windows.Forms.RadioButton rBmap;
        private System.Windows.Forms.RadioButton rBtree;
    }
}

