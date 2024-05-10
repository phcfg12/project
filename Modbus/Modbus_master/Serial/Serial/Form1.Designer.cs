namespace Serial
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.comboBox2 = new System.Windows.Forms.ComboBox();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.button1 = new System.Windows.Forms.Button();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.button2 = new System.Windows.Forms.Button();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.button3 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.tBoxSlaveID = new System.Windows.Forms.TextBox();
            this.tBoxStartAddress = new System.Windows.Forms.TextBox();
            this.tBoxNumofPoints = new System.Windows.Forms.TextBox();
            this.fcnCode = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.tBoxValue = new System.Windows.Forms.TextBox();
            this.d1On = new System.Windows.Forms.Button();
            this.d1Off = new System.Windows.Forms.Button();
            this.d2On = new System.Windows.Forms.Button();
            this.d2Off = new System.Windows.Forms.Button();
            this.label8 = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // comboBox1
            // 
            this.comboBox1.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Location = new System.Drawing.Point(94, 52);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(121, 24);
            this.comboBox1.TabIndex = 0;
            // 
            // comboBox2
            // 
            this.comboBox2.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox2.FormattingEnabled = true;
            this.comboBox2.Items.AddRange(new object[] {
            "9600",
            "115200"});
            this.comboBox2.Location = new System.Drawing.Point(309, 52);
            this.comboBox2.Name = "comboBox2";
            this.comboBox2.Size = new System.Drawing.Size(121, 24);
            this.comboBox2.TabIndex = 1;
            // 
            // progressBar1
            // 
            this.progressBar1.Location = new System.Drawing.Point(622, 53);
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(100, 23);
            this.progressBar1.TabIndex = 2;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.button1);
            this.groupBox1.Controls.Add(this.textBox1);
            this.groupBox1.Location = new System.Drawing.Point(94, 222);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(238, 118);
            this.groupBox1.TabIndex = 3;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Send Here";
            // 
            // button1
            // 
            this.button1.Enabled = false;
            this.button1.Location = new System.Drawing.Point(157, 87);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 1;
            this.button1.Text = "Send";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // textBox1
            // 
            this.textBox1.Enabled = false;
            this.textBox1.Location = new System.Drawing.Point(7, 22);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(225, 59);
            this.textBox1.TabIndex = 0;
            this.textBox1.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.button2);
            this.groupBox2.Controls.Add(this.textBox2);
            this.groupBox2.Location = new System.Drawing.Point(362, 222);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(238, 118);
            this.groupBox2.TabIndex = 4;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Recieved Here";
            // 
            // button2
            // 
            this.button2.Enabled = false;
            this.button2.Location = new System.Drawing.Point(157, 87);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(75, 23);
            this.button2.TabIndex = 10;
            this.button2.Text = "Read";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // textBox2
            // 
            this.textBox2.Enabled = false;
            this.textBox2.Location = new System.Drawing.Point(7, 21);
            this.textBox2.Multiline = true;
            this.textBox2.Name = "textBox2";
            this.textBox2.ReadOnly = true;
            this.textBox2.Size = new System.Drawing.Size(225, 60);
            this.textBox2.TabIndex = 0;
            this.textBox2.TextChanged += new System.EventHandler(this.textBox2_TextChanged);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(657, 166);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(85, 68);
            this.button3.TabIndex = 5;
            this.button3.Text = "Open Port";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // button4
            // 
            this.button4.Enabled = false;
            this.button4.Location = new System.Drawing.Point(657, 254);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(85, 68);
            this.button4.TabIndex = 6;
            this.button4.Text = "Close Port";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(91, 30);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(78, 16);
            this.label1.TabIndex = 7;
            this.label1.Text = "Port Names";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(306, 30);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(65, 16);
            this.label2.TabIndex = 8;
            this.label2.Text = "Baud rate";
            this.label2.Click += new System.EventHandler(this.label2_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(622, 29);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(44, 16);
            this.label3.TabIndex = 9;
            this.label3.Text = "Status";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(91, 92);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(58, 16);
            this.label4.TabIndex = 10;
            this.label4.Text = "Slave ID";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(235, 92);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(88, 16);
            this.label5.TabIndex = 11;
            this.label5.Text = "Start Address";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(385, 92);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(109, 16);
            this.label6.TabIndex = 12;
            this.label6.Text = "Number of Points";
            // 
            // tBoxSlaveID
            // 
            this.tBoxSlaveID.Location = new System.Drawing.Point(94, 111);
            this.tBoxSlaveID.Name = "tBoxSlaveID";
            this.tBoxSlaveID.Size = new System.Drawing.Size(100, 22);
            this.tBoxSlaveID.TabIndex = 13;
            // 
            // tBoxStartAddress
            // 
            this.tBoxStartAddress.Location = new System.Drawing.Point(238, 111);
            this.tBoxStartAddress.Name = "tBoxStartAddress";
            this.tBoxStartAddress.Size = new System.Drawing.Size(100, 22);
            this.tBoxStartAddress.TabIndex = 14;
            // 
            // tBoxNumofPoints
            // 
            this.tBoxNumofPoints.Location = new System.Drawing.Point(388, 111);
            this.tBoxNumofPoints.Name = "tBoxNumofPoints";
            this.tBoxNumofPoints.Size = new System.Drawing.Size(100, 22);
            this.tBoxNumofPoints.TabIndex = 15;
            // 
            // fcnCode
            // 
            this.fcnCode.Location = new System.Drawing.Point(94, 166);
            this.fcnCode.Name = "fcnCode";
            this.fcnCode.Size = new System.Drawing.Size(100, 22);
            this.fcnCode.TabIndex = 16;
            this.fcnCode.TextChanged += new System.EventHandler(this.fcnCode_TextChanged);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(91, 147);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(93, 16);
            this.label7.TabIndex = 17;
            this.label7.Text = "Function Code";
            // 
            // tBoxValue
            // 
            this.tBoxValue.Location = new System.Drawing.Point(238, 166);
            this.tBoxValue.Name = "tBoxValue";
            this.tBoxValue.Size = new System.Drawing.Size(362, 22);
            this.tBoxValue.TabIndex = 18;
            // 
            // d1On
            // 
            this.d1On.Location = new System.Drawing.Point(94, 359);
            this.d1On.Name = "d1On";
            this.d1On.Size = new System.Drawing.Size(75, 23);
            this.d1On.TabIndex = 19;
            this.d1On.Text = "D1 ON";
            this.d1On.UseVisualStyleBackColor = true;
            this.d1On.Click += new System.EventHandler(this.d1On_Click);
            // 
            // d1Off
            // 
            this.d1Off.Location = new System.Drawing.Point(94, 388);
            this.d1Off.Name = "d1Off";
            this.d1Off.Size = new System.Drawing.Size(75, 23);
            this.d1Off.TabIndex = 20;
            this.d1Off.Text = "D1 OFF";
            this.d1Off.UseVisualStyleBackColor = true;
            this.d1Off.Click += new System.EventHandler(this.d1Off_Click);
            // 
            // d2On
            // 
            this.d2On.Location = new System.Drawing.Point(257, 359);
            this.d2On.Name = "d2On";
            this.d2On.Size = new System.Drawing.Size(75, 23);
            this.d2On.TabIndex = 21;
            this.d2On.Text = "D2 ON";
            this.d2On.UseVisualStyleBackColor = true;
            this.d2On.Click += new System.EventHandler(this.d2On_Click);
            // 
            // d2Off
            // 
            this.d2Off.Location = new System.Drawing.Point(257, 388);
            this.d2Off.Name = "d2Off";
            this.d2Off.Size = new System.Drawing.Size(75, 23);
            this.d2Off.TabIndex = 22;
            this.d2Off.Text = "D2 OFF";
            this.d2Off.UseVisualStyleBackColor = true;
            this.d2Off.Click += new System.EventHandler(this.d2Off_Click);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(235, 147);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(42, 16);
            this.label8.TabIndex = 23;
            this.label8.Text = "Value";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ActiveBorder;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.d2Off);
            this.Controls.Add(this.d2On);
            this.Controls.Add(this.d1Off);
            this.Controls.Add(this.d1On);
            this.Controls.Add(this.tBoxValue);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.fcnCode);
            this.Controls.Add(this.tBoxNumofPoints);
            this.Controls.Add(this.tBoxStartAddress);
            this.Controls.Add(this.tBoxSlaveID);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.progressBar1);
            this.Controls.Add(this.comboBox2);
            this.Controls.Add(this.comboBox1);
            this.Name = "Form1";
            this.Text = "Serial Communication";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.ComboBox comboBox2;
        private System.Windows.Forms.ProgressBar progressBar1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox tBoxSlaveID;
        private System.Windows.Forms.TextBox tBoxStartAddress;
        private System.Windows.Forms.TextBox tBoxNumofPoints;
        private System.Windows.Forms.TextBox fcnCode;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox tBoxValue;
        private System.Windows.Forms.Button d1On;
        private System.Windows.Forms.Button d1Off;
        private System.Windows.Forms.Button d2On;
        private System.Windows.Forms.Button d2Off;
        private System.Windows.Forms.Label label8;
    }
}

