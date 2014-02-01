namespace halForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.myMenuStrip = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.mySerialPort = new System.IO.Ports.SerialPort(this.components);
            this.myTabControl = new System.Windows.Forms.TabControl();
            this.ganTab = new System.Windows.Forms.TabPage();
            this.button5 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.lblPollTime = new System.Windows.Forms.Label();
            this.comboBoxTime = new System.Windows.Forms.ComboBox();
            this.checkBoxStatus = new System.Windows.Forms.CheckBox();
            this.checkBoxMinToTray = new System.Windows.Forms.CheckBox();
            this.Logo = new System.Windows.Forms.PictureBox();
            this.USBTab = new System.Windows.Forms.TabPage();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.statusLabel = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.baudRateCombobox = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.comListComboBox = new System.Windows.Forms.ComboBox();
            this.button16 = new System.Windows.Forms.Button();
            this.richTextBox1 = new System.Windows.Forms.RichTextBox();
            this.clearTxButton = new System.Windows.Forms.Button();
            this.sendButton = new System.Windows.Forms.Button();
            this.btnApplyUSB = new System.Windows.Forms.Button();
            this.btnCancelUSB = new System.Windows.Forms.Button();
            this.btnOkayUSB = new System.Windows.Forms.Button();
            this.rxRichTextbox = new System.Windows.Forms.RichTextBox();
            this.InternetTab = new System.Windows.Forms.TabPage();
            this.btnApplyInternet = new System.Windows.Forms.Button();
            this.btnCancelInternet = new System.Windows.Forms.Button();
            this.btnOkayInternet = new System.Windows.Forms.Button();
            this.button6 = new System.Windows.Forms.Button();
            this.textBox9 = new System.Windows.Forms.TextBox();
            this.textBox10 = new System.Windows.Forms.TextBox();
            this.textBox7 = new System.Windows.Forms.TextBox();
            this.textBox8 = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.ScheduleTab = new System.Windows.Forms.TabPage();
            this.btnApplySchedule = new System.Windows.Forms.Button();
            this.btnCancelSchedule = new System.Windows.Forms.Button();
            this.btnOkaySchedule = new System.Windows.Forms.Button();
            this.IOTab = new System.Windows.Forms.TabPage();
            this.myStatusStrip = new System.Windows.Forms.StatusStrip();
            this.statusLabelSerial = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel3 = new System.Windows.Forms.ToolStripStatusLabel();
            this.statusLabelEthernet = new System.Windows.Forms.ToolStripStatusLabel();
            this.btnApplyIO = new System.Windows.Forms.Button();
            this.btnCancelIO = new System.Windows.Forms.Button();
            this.btnOkayIO = new System.Windows.Forms.Button();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.lblRelay4State = new System.Windows.Forms.Label();
            this.lblRelay4 = new System.Windows.Forms.Label();
            this.comboRelay4Command = new System.Windows.Forms.ComboBox();
            this.lblRelay3State = new System.Windows.Forms.Label();
            this.lblRelay3 = new System.Windows.Forms.Label();
            this.comboRelay3Command = new System.Windows.Forms.ComboBox();
            this.lblRelay2State = new System.Windows.Forms.Label();
            this.lblRelay2 = new System.Windows.Forms.Label();
            this.comboRelay2Command = new System.Windows.Forms.ComboBox();
            this.lblRelay1State = new System.Windows.Forms.Label();
            this.lblRelay1 = new System.Windows.Forms.Label();
            this.comboRelay1Command = new System.Windows.Forms.ComboBox();
            this.btnWriteRelay = new System.Windows.Forms.Button();
            this.btnReadRelay = new System.Windows.Forms.Button();
            this.myNotifyIcon = new System.Windows.Forms.NotifyIcon(this.components);
            this.ScheduleData = new System.Windows.Forms.DataGridView();
            this.ID = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.StartTime = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.End = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Relays = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.btnLoadSchedule = new System.Windows.Forms.Button();
            this.myMenuStrip.SuspendLayout();
            this.myTabControl.SuspendLayout();
            this.ganTab.SuspendLayout();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.Logo)).BeginInit();
            this.USBTab.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.InternetTab.SuspendLayout();
            this.ScheduleTab.SuspendLayout();
            this.IOTab.SuspendLayout();
            this.myStatusStrip.SuspendLayout();
            this.groupBox3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ScheduleData)).BeginInit();
            this.SuspendLayout();
            // 
            // myMenuStrip
            // 
            this.myMenuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem});
            this.myMenuStrip.Location = new System.Drawing.Point(0, 0);
            this.myMenuStrip.Name = "myMenuStrip";
            this.myMenuStrip.Size = new System.Drawing.Size(492, 24);
            this.myMenuStrip.TabIndex = 0;
            this.myMenuStrip.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(92, 22);
            this.exitToolStripMenuItem.Text = "E&xit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.Close_App);
            // 
            // mySerialPort
            // 
            this.mySerialPort.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort1_DataReceived);
            // 
            // myTabControl
            // 
            this.myTabControl.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.myTabControl.Controls.Add(this.ganTab);
            this.myTabControl.Controls.Add(this.USBTab);
            this.myTabControl.Controls.Add(this.InternetTab);
            this.myTabControl.Controls.Add(this.ScheduleTab);
            this.myTabControl.Controls.Add(this.IOTab);
            this.myTabControl.Location = new System.Drawing.Point(0, 27);
            this.myTabControl.Name = "myTabControl";
            this.myTabControl.SelectedIndex = 0;
            this.myTabControl.Size = new System.Drawing.Size(492, 493);
            this.myTabControl.SizeMode = System.Windows.Forms.TabSizeMode.FillToRight;
            this.myTabControl.TabIndex = 3;
            // 
            // ganTab
            // 
            this.ganTab.BackColor = System.Drawing.Color.Gainsboro;
            this.ganTab.Controls.Add(this.button5);
            this.ganTab.Controls.Add(this.button4);
            this.ganTab.Controls.Add(this.button3);
            this.ganTab.Controls.Add(this.groupBox2);
            this.ganTab.Controls.Add(this.Logo);
            this.ganTab.Location = new System.Drawing.Point(4, 22);
            this.ganTab.Name = "ganTab";
            this.ganTab.Size = new System.Drawing.Size(484, 467);
            this.ganTab.TabIndex = 3;
            this.ganTab.Text = "General";
            // 
            // button5
            // 
            this.button5.Enabled = false;
            this.button5.Location = new System.Drawing.Point(406, 410);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(75, 33);
            this.button5.TabIndex = 5;
            this.button5.Text = "Apply";
            this.button5.UseVisualStyleBackColor = true;
            this.button5.Click += new System.EventHandler(this.button5_Click);
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(325, 410);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(75, 33);
            this.button4.TabIndex = 4;
            this.button4.Text = "Cancel";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.Close_App);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(244, 410);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(75, 33);
            this.button3.TabIndex = 3;
            this.button3.Text = "Okay";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.okayButton_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.lblPollTime);
            this.groupBox2.Controls.Add(this.comboBoxTime);
            this.groupBox2.Controls.Add(this.checkBoxStatus);
            this.groupBox2.Controls.Add(this.checkBoxMinToTray);
            this.groupBox2.Location = new System.Drawing.Point(8, 172);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(468, 100);
            this.groupBox2.TabIndex = 2;
            this.groupBox2.TabStop = false;
            // 
            // lblPollTime
            // 
            this.lblPollTime.AutoSize = true;
            this.lblPollTime.Enabled = false;
            this.lblPollTime.Location = new System.Drawing.Point(171, 44);
            this.lblPollTime.Name = "lblPollTime";
            this.lblPollTime.Size = new System.Drawing.Size(37, 13);
            this.lblPollTime.TabIndex = 3;
            this.lblPollTime.Text = "Every:";
            // 
            // comboBoxTime
            // 
            this.comboBoxTime.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxTime.Enabled = false;
            this.comboBoxTime.FormattingEnabled = true;
            this.comboBoxTime.Items.AddRange(new object[] {
            "30 secs",
            "1 min",
            "5 min",
            "10 min",
            "30 min",
            "1 hr",
            "5 hr",
            "12 hr",
            "1 day"});
            this.comboBoxTime.Location = new System.Drawing.Point(214, 41);
            this.comboBoxTime.Name = "comboBoxTime";
            this.comboBoxTime.Size = new System.Drawing.Size(72, 21);
            this.comboBoxTime.TabIndex = 2;
            // 
            // checkBoxStatus
            // 
            this.checkBoxStatus.AutoSize = true;
            this.checkBoxStatus.Location = new System.Drawing.Point(7, 43);
            this.checkBoxStatus.Name = "checkBoxStatus";
            this.checkBoxStatus.Size = new System.Drawing.Size(124, 17);
            this.checkBoxStatus.TabIndex = 1;
            this.checkBoxStatus.Text = "Check status of HAL";
            this.checkBoxStatus.UseVisualStyleBackColor = true;
            this.checkBoxStatus.CheckedChanged += new System.EventHandler(this.checkBox2_CheckedChanged);
            // 
            // checkBoxMinToTray
            // 
            this.checkBoxMinToTray.AutoSize = true;
            this.checkBoxMinToTray.Location = new System.Drawing.Point(7, 20);
            this.checkBoxMinToTray.Name = "checkBoxMinToTray";
            this.checkBoxMinToTray.Size = new System.Drawing.Size(102, 17);
            this.checkBoxMinToTray.TabIndex = 0;
            this.checkBoxMinToTray.Text = "Minimize to Tray";
            this.checkBoxMinToTray.UseVisualStyleBackColor = true;
            // 
            // Logo
            // 
            this.Logo.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.Logo.Image = ((System.Drawing.Image)(resources.GetObject("Logo.Image")));
            this.Logo.InitialImage = ((System.Drawing.Image)(resources.GetObject("Logo.InitialImage")));
            this.Logo.Location = new System.Drawing.Point(3, 4);
            this.Logo.Name = "Logo";
            this.Logo.Size = new System.Drawing.Size(473, 159);
            this.Logo.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.Logo.TabIndex = 0;
            this.Logo.TabStop = false;
            // 
            // USBTab
            // 
            this.USBTab.BackColor = System.Drawing.Color.Gainsboro;
            this.USBTab.Controls.Add(this.groupBox1);
            this.USBTab.Controls.Add(this.button16);
            this.USBTab.Controls.Add(this.richTextBox1);
            this.USBTab.Controls.Add(this.clearTxButton);
            this.USBTab.Controls.Add(this.sendButton);
            this.USBTab.Controls.Add(this.btnApplyUSB);
            this.USBTab.Controls.Add(this.btnCancelUSB);
            this.USBTab.Controls.Add(this.btnOkayUSB);
            this.USBTab.Controls.Add(this.rxRichTextbox);
            this.USBTab.ForeColor = System.Drawing.Color.Black;
            this.USBTab.Location = new System.Drawing.Point(4, 22);
            this.USBTab.Name = "USBTab";
            this.USBTab.Padding = new System.Windows.Forms.Padding(3);
            this.USBTab.Size = new System.Drawing.Size(484, 467);
            this.USBTab.TabIndex = 0;
            this.USBTab.Text = "Setup USB";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.statusLabel);
            this.groupBox1.Controls.Add(this.button1);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.baudRateCombobox);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.comListComboBox);
            this.groupBox1.ForeColor = System.Drawing.SystemColors.ControlText;
            this.groupBox1.Location = new System.Drawing.Point(8, 16);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(205, 100);
            this.groupBox1.TabIndex = 19;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "COM Connect";
            // 
            // statusLabel
            // 
            this.statusLabel.AutoSize = true;
            this.statusLabel.Location = new System.Drawing.Point(92, 76);
            this.statusLabel.Name = "statusLabel";
            this.statusLabel.Size = new System.Drawing.Size(109, 13);
            this.statusLabel.TabIndex = 4;
            this.statusLabel.Text = "Status: Disconnected";
            // 
            // button1
            // 
            this.button1.ForeColor = System.Drawing.SystemColors.ControlText;
            this.button1.Location = new System.Drawing.Point(6, 71);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 1;
            this.button1.Text = "Connect";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.ForeColor = System.Drawing.SystemColors.ControlText;
            this.label2.Location = new System.Drawing.Point(105, 49);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(58, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Baud Rate";
            // 
            // baudRateCombobox
            // 
            this.baudRateCombobox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.baudRateCombobox.Enabled = false;
            this.baudRateCombobox.ForeColor = System.Drawing.SystemColors.ControlText;
            this.baudRateCombobox.FormattingEnabled = true;
            this.baudRateCombobox.Items.AddRange(new object[] {
            "9600"});
            this.baudRateCombobox.Location = new System.Drawing.Point(6, 46);
            this.baudRateCombobox.Name = "baudRateCombobox";
            this.baudRateCombobox.Size = new System.Drawing.Size(93, 21);
            this.baudRateCombobox.TabIndex = 2;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.ForeColor = System.Drawing.SystemColors.ControlText;
            this.label1.Location = new System.Drawing.Point(92, 22);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(53, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "COM Port";
            // 
            // comListComboBox
            // 
            this.comListComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comListComboBox.Enabled = false;
            this.comListComboBox.ForeColor = System.Drawing.SystemColors.ControlText;
            this.comListComboBox.FormattingEnabled = true;
            this.comListComboBox.Location = new System.Drawing.Point(6, 19);
            this.comListComboBox.Name = "comListComboBox";
            this.comListComboBox.Size = new System.Drawing.Size(70, 21);
            this.comListComboBox.TabIndex = 0;
            // 
            // button16
            // 
            this.button16.Location = new System.Drawing.Point(116, 350);
            this.button16.Name = "button16";
            this.button16.Size = new System.Drawing.Size(75, 23);
            this.button16.TabIndex = 18;
            this.button16.Text = "Sync Time";
            this.button16.UseVisualStyleBackColor = true;
            this.button16.Click += new System.EventHandler(this.button16_Click);
            // 
            // richTextBox1
            // 
            this.richTextBox1.Location = new System.Drawing.Point(6, 316);
            this.richTextBox1.Multiline = false;
            this.richTextBox1.Name = "richTextBox1";
            this.richTextBox1.Size = new System.Drawing.Size(470, 28);
            this.richTextBox1.TabIndex = 17;
            this.richTextBox1.Text = "";
            // 
            // clearTxButton
            // 
            this.clearTxButton.Location = new System.Drawing.Point(8, 379);
            this.clearTxButton.Name = "clearTxButton";
            this.clearTxButton.Size = new System.Drawing.Size(70, 23);
            this.clearTxButton.TabIndex = 16;
            this.clearTxButton.Text = "Clear Tx Buffer";
            this.clearTxButton.UseVisualStyleBackColor = true;
            this.clearTxButton.Click += new System.EventHandler(this.clearTxButton_Click);
            // 
            // sendButton
            // 
            this.sendButton.Location = new System.Drawing.Point(8, 350);
            this.sendButton.Name = "sendButton";
            this.sendButton.Size = new System.Drawing.Size(70, 23);
            this.sendButton.TabIndex = 15;
            this.sendButton.Text = "Send";
            this.sendButton.UseVisualStyleBackColor = true;
            this.sendButton.Click += new System.EventHandler(this.sendButton_Click);
            // 
            // btnApplyUSB
            // 
            this.btnApplyUSB.Enabled = false;
            this.btnApplyUSB.Location = new System.Drawing.Point(406, 411);
            this.btnApplyUSB.Name = "btnApplyUSB";
            this.btnApplyUSB.Size = new System.Drawing.Size(75, 33);
            this.btnApplyUSB.TabIndex = 8;
            this.btnApplyUSB.Text = "Apply";
            this.btnApplyUSB.UseVisualStyleBackColor = true;
            // 
            // btnCancelUSB
            // 
            this.btnCancelUSB.Location = new System.Drawing.Point(325, 411);
            this.btnCancelUSB.Name = "btnCancelUSB";
            this.btnCancelUSB.Size = new System.Drawing.Size(75, 33);
            this.btnCancelUSB.TabIndex = 7;
            this.btnCancelUSB.Text = "Cancel";
            this.btnCancelUSB.UseVisualStyleBackColor = true;
            this.btnCancelUSB.Click += new System.EventHandler(this.Close_App);
            // 
            // btnOkayUSB
            // 
            this.btnOkayUSB.Location = new System.Drawing.Point(244, 411);
            this.btnOkayUSB.Name = "btnOkayUSB";
            this.btnOkayUSB.Size = new System.Drawing.Size(75, 33);
            this.btnOkayUSB.TabIndex = 6;
            this.btnOkayUSB.Text = "Okay";
            this.btnOkayUSB.UseVisualStyleBackColor = true;
            this.btnOkayUSB.Click += new System.EventHandler(this.okayButton_Click);
            // 
            // rxRichTextbox
            // 
            this.rxRichTextbox.Location = new System.Drawing.Point(6, 122);
            this.rxRichTextbox.Name = "rxRichTextbox";
            this.rxRichTextbox.ReadOnly = true;
            this.rxRichTextbox.ScrollBars = System.Windows.Forms.RichTextBoxScrollBars.Vertical;
            this.rxRichTextbox.Size = new System.Drawing.Size(470, 188);
            this.rxRichTextbox.TabIndex = 1;
            this.rxRichTextbox.Text = "";
            // 
            // InternetTab
            // 
            this.InternetTab.BackColor = System.Drawing.Color.Gainsboro;
            this.InternetTab.Controls.Add(this.btnApplyInternet);
            this.InternetTab.Controls.Add(this.btnCancelInternet);
            this.InternetTab.Controls.Add(this.btnOkayInternet);
            this.InternetTab.Controls.Add(this.button6);
            this.InternetTab.Controls.Add(this.textBox9);
            this.InternetTab.Controls.Add(this.textBox10);
            this.InternetTab.Controls.Add(this.textBox7);
            this.InternetTab.Controls.Add(this.textBox8);
            this.InternetTab.Controls.Add(this.label6);
            this.InternetTab.Controls.Add(this.label5);
            this.InternetTab.ForeColor = System.Drawing.Color.Black;
            this.InternetTab.Location = new System.Drawing.Point(4, 22);
            this.InternetTab.Name = "InternetTab";
            this.InternetTab.Padding = new System.Windows.Forms.Padding(3);
            this.InternetTab.Size = new System.Drawing.Size(484, 467);
            this.InternetTab.TabIndex = 1;
            this.InternetTab.Text = "Internet Configuration";
            // 
            // btnApplyInternet
            // 
            this.btnApplyInternet.Enabled = false;
            this.btnApplyInternet.Location = new System.Drawing.Point(401, 394);
            this.btnApplyInternet.Name = "btnApplyInternet";
            this.btnApplyInternet.Size = new System.Drawing.Size(75, 33);
            this.btnApplyInternet.TabIndex = 16;
            this.btnApplyInternet.Text = "Apply";
            this.btnApplyInternet.UseVisualStyleBackColor = true;
            // 
            // btnCancelInternet
            // 
            this.btnCancelInternet.Location = new System.Drawing.Point(320, 394);
            this.btnCancelInternet.Name = "btnCancelInternet";
            this.btnCancelInternet.Size = new System.Drawing.Size(75, 33);
            this.btnCancelInternet.TabIndex = 15;
            this.btnCancelInternet.Text = "Cancel";
            this.btnCancelInternet.UseVisualStyleBackColor = true;
            this.btnCancelInternet.Click += new System.EventHandler(this.Close_App);
            // 
            // btnOkayInternet
            // 
            this.btnOkayInternet.Location = new System.Drawing.Point(239, 394);
            this.btnOkayInternet.Name = "btnOkayInternet";
            this.btnOkayInternet.Size = new System.Drawing.Size(75, 33);
            this.btnOkayInternet.TabIndex = 14;
            this.btnOkayInternet.Text = "Okay";
            this.btnOkayInternet.UseVisualStyleBackColor = true;
            this.btnOkayInternet.Click += new System.EventHandler(this.okayButton_Click);
            // 
            // button6
            // 
            this.button6.ForeColor = System.Drawing.Color.Black;
            this.button6.Location = new System.Drawing.Point(112, 85);
            this.button6.Name = "button6";
            this.button6.Size = new System.Drawing.Size(114, 23);
            this.button6.TabIndex = 13;
            this.button6.Text = "Test Connection";
            this.button6.UseVisualStyleBackColor = true;
            // 
            // textBox9
            // 
            this.textBox9.Location = new System.Drawing.Point(223, 56);
            this.textBox9.Name = "textBox9";
            this.textBox9.Size = new System.Drawing.Size(31, 20);
            this.textBox9.TabIndex = 12;
            // 
            // textBox10
            // 
            this.textBox10.Location = new System.Drawing.Point(186, 56);
            this.textBox10.Name = "textBox10";
            this.textBox10.Size = new System.Drawing.Size(31, 20);
            this.textBox10.TabIndex = 11;
            // 
            // textBox7
            // 
            this.textBox7.Location = new System.Drawing.Point(150, 56);
            this.textBox7.Name = "textBox7";
            this.textBox7.Size = new System.Drawing.Size(31, 20);
            this.textBox7.TabIndex = 10;
            // 
            // textBox8
            // 
            this.textBox8.Location = new System.Drawing.Point(113, 56);
            this.textBox8.Name = "textBox8";
            this.textBox8.Size = new System.Drawing.Size(31, 20);
            this.textBox8.TabIndex = 9;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(45, 90);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(61, 13);
            this.label6.TabIndex = 2;
            this.label6.Text = "IP Address:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(45, 56);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(61, 13);
            this.label5.TabIndex = 1;
            this.label5.Text = "IP Address:";
            // 
            // ScheduleTab
            // 
            this.ScheduleTab.BackColor = System.Drawing.Color.Gainsboro;
            this.ScheduleTab.Controls.Add(this.btnLoadSchedule);
            this.ScheduleTab.Controls.Add(this.ScheduleData);
            this.ScheduleTab.Controls.Add(this.btnApplySchedule);
            this.ScheduleTab.Controls.Add(this.btnCancelSchedule);
            this.ScheduleTab.Controls.Add(this.btnOkaySchedule);
            this.ScheduleTab.Location = new System.Drawing.Point(4, 22);
            this.ScheduleTab.Name = "ScheduleTab";
            this.ScheduleTab.Size = new System.Drawing.Size(484, 467);
            this.ScheduleTab.TabIndex = 2;
            this.ScheduleTab.Text = "Manage Schedule";
            // 
            // btnApplySchedule
            // 
            this.btnApplySchedule.Enabled = false;
            this.btnApplySchedule.Location = new System.Drawing.Point(377, 379);
            this.btnApplySchedule.Name = "btnApplySchedule";
            this.btnApplySchedule.Size = new System.Drawing.Size(75, 33);
            this.btnApplySchedule.TabIndex = 8;
            this.btnApplySchedule.Text = "Apply";
            this.btnApplySchedule.UseVisualStyleBackColor = true;
            // 
            // btnCancelSchedule
            // 
            this.btnCancelSchedule.Location = new System.Drawing.Point(296, 379);
            this.btnCancelSchedule.Name = "btnCancelSchedule";
            this.btnCancelSchedule.Size = new System.Drawing.Size(75, 33);
            this.btnCancelSchedule.TabIndex = 7;
            this.btnCancelSchedule.Text = "Cancel";
            this.btnCancelSchedule.UseVisualStyleBackColor = true;
            this.btnCancelSchedule.Click += new System.EventHandler(this.Close_App);
            // 
            // btnOkaySchedule
            // 
            this.btnOkaySchedule.Location = new System.Drawing.Point(215, 379);
            this.btnOkaySchedule.Name = "btnOkaySchedule";
            this.btnOkaySchedule.Size = new System.Drawing.Size(75, 33);
            this.btnOkaySchedule.TabIndex = 6;
            this.btnOkaySchedule.Text = "Okay";
            this.btnOkaySchedule.UseVisualStyleBackColor = true;
            this.btnOkaySchedule.Click += new System.EventHandler(this.okayButton_Click);
            // 
            // IOTab
            // 
            this.IOTab.BackColor = System.Drawing.Color.Gainsboro;
            this.IOTab.Controls.Add(this.myStatusStrip);
            this.IOTab.Controls.Add(this.btnApplyIO);
            this.IOTab.Controls.Add(this.btnCancelIO);
            this.IOTab.Controls.Add(this.btnOkayIO);
            this.IOTab.Controls.Add(this.groupBox3);
            this.IOTab.Location = new System.Drawing.Point(4, 22);
            this.IOTab.Name = "IOTab";
            this.IOTab.Padding = new System.Windows.Forms.Padding(3);
            this.IOTab.Size = new System.Drawing.Size(484, 467);
            this.IOTab.TabIndex = 4;
            this.IOTab.Text = "IO";
            // 
            // myStatusStrip
            // 
            this.myStatusStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.statusLabelSerial,
            this.toolStripStatusLabel3,
            this.statusLabelEthernet});
            this.myStatusStrip.Location = new System.Drawing.Point(3, 442);
            this.myStatusStrip.Name = "myStatusStrip";
            this.myStatusStrip.Size = new System.Drawing.Size(478, 22);
            this.myStatusStrip.TabIndex = 24;
            this.myStatusStrip.Text = "myStatusStrip";
            // 
            // statusLabelSerial
            // 
            this.statusLabelSerial.Name = "statusLabelSerial";
            this.statusLabelSerial.Size = new System.Drawing.Size(113, 17);
            this.statusLabelSerial.Text = "Serial: Disconnected";
            // 
            // toolStripStatusLabel3
            // 
            this.toolStripStatusLabel3.Name = "toolStripStatusLabel3";
            this.toolStripStatusLabel3.Size = new System.Drawing.Size(16, 17);
            this.toolStripStatusLabel3.Text = " | ";
            // 
            // statusLabelEthernet
            // 
            this.statusLabelEthernet.Name = "statusLabelEthernet";
            this.statusLabelEthernet.Size = new System.Drawing.Size(129, 17);
            this.statusLabelEthernet.Text = "Ethernet: Disconnected";
            // 
            // btnApplyIO
            // 
            this.btnApplyIO.Enabled = false;
            this.btnApplyIO.Location = new System.Drawing.Point(401, 389);
            this.btnApplyIO.Name = "btnApplyIO";
            this.btnApplyIO.Size = new System.Drawing.Size(75, 33);
            this.btnApplyIO.TabIndex = 23;
            this.btnApplyIO.Text = "Apply";
            this.btnApplyIO.UseVisualStyleBackColor = true;
            // 
            // btnCancelIO
            // 
            this.btnCancelIO.Location = new System.Drawing.Point(320, 389);
            this.btnCancelIO.Name = "btnCancelIO";
            this.btnCancelIO.Size = new System.Drawing.Size(75, 33);
            this.btnCancelIO.TabIndex = 22;
            this.btnCancelIO.Text = "Cancel";
            this.btnCancelIO.UseVisualStyleBackColor = true;
            this.btnCancelIO.Click += new System.EventHandler(this.Close_App);
            // 
            // btnOkayIO
            // 
            this.btnOkayIO.Location = new System.Drawing.Point(239, 389);
            this.btnOkayIO.Name = "btnOkayIO";
            this.btnOkayIO.Size = new System.Drawing.Size(75, 33);
            this.btnOkayIO.TabIndex = 21;
            this.btnOkayIO.Text = "Okay";
            this.btnOkayIO.UseVisualStyleBackColor = true;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.lblRelay4State);
            this.groupBox3.Controls.Add(this.lblRelay4);
            this.groupBox3.Controls.Add(this.comboRelay4Command);
            this.groupBox3.Controls.Add(this.lblRelay3State);
            this.groupBox3.Controls.Add(this.lblRelay3);
            this.groupBox3.Controls.Add(this.comboRelay3Command);
            this.groupBox3.Controls.Add(this.lblRelay2State);
            this.groupBox3.Controls.Add(this.lblRelay2);
            this.groupBox3.Controls.Add(this.comboRelay2Command);
            this.groupBox3.Controls.Add(this.lblRelay1State);
            this.groupBox3.Controls.Add(this.lblRelay1);
            this.groupBox3.Controls.Add(this.comboRelay1Command);
            this.groupBox3.Controls.Add(this.btnWriteRelay);
            this.groupBox3.Controls.Add(this.btnReadRelay);
            this.groupBox3.Location = new System.Drawing.Point(135, 42);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(241, 168);
            this.groupBox3.TabIndex = 20;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "IO";
            // 
            // lblRelay4State
            // 
            this.lblRelay4State.AutoSize = true;
            this.lblRelay4State.Location = new System.Drawing.Point(68, 107);
            this.lblRelay4State.Name = "lblRelay4State";
            this.lblRelay4State.Size = new System.Drawing.Size(21, 13);
            this.lblRelay4State.TabIndex = 17;
            this.lblRelay4State.Text = "Off";
            // 
            // lblRelay4
            // 
            this.lblRelay4.AutoSize = true;
            this.lblRelay4.Location = new System.Drawing.Point(7, 107);
            this.lblRelay4.Name = "lblRelay4";
            this.lblRelay4.Size = new System.Drawing.Size(43, 13);
            this.lblRelay4.TabIndex = 16;
            this.lblRelay4.Text = "Relay4:";
            // 
            // comboRelay4Command
            // 
            this.comboRelay4Command.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboRelay4Command.FormattingEnabled = true;
            this.comboRelay4Command.Items.AddRange(new object[] {
            "Ignore",
            "On",
            "Off",
            "Toggle"});
            this.comboRelay4Command.Location = new System.Drawing.Point(95, 104);
            this.comboRelay4Command.Name = "comboRelay4Command";
            this.comboRelay4Command.Size = new System.Drawing.Size(84, 21);
            this.comboRelay4Command.TabIndex = 15;
            // 
            // lblRelay3State
            // 
            this.lblRelay3State.AutoSize = true;
            this.lblRelay3State.Location = new System.Drawing.Point(68, 80);
            this.lblRelay3State.Name = "lblRelay3State";
            this.lblRelay3State.Size = new System.Drawing.Size(21, 13);
            this.lblRelay3State.TabIndex = 14;
            this.lblRelay3State.Text = "Off";
            // 
            // lblRelay3
            // 
            this.lblRelay3.AutoSize = true;
            this.lblRelay3.Location = new System.Drawing.Point(7, 80);
            this.lblRelay3.Name = "lblRelay3";
            this.lblRelay3.Size = new System.Drawing.Size(43, 13);
            this.lblRelay3.TabIndex = 13;
            this.lblRelay3.Text = "Relay3:";
            // 
            // comboRelay3Command
            // 
            this.comboRelay3Command.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboRelay3Command.FormattingEnabled = true;
            this.comboRelay3Command.Items.AddRange(new object[] {
            "Ignore",
            "On",
            "Off",
            "Toggle"});
            this.comboRelay3Command.Location = new System.Drawing.Point(95, 77);
            this.comboRelay3Command.Name = "comboRelay3Command";
            this.comboRelay3Command.Size = new System.Drawing.Size(84, 21);
            this.comboRelay3Command.TabIndex = 12;
            // 
            // lblRelay2State
            // 
            this.lblRelay2State.AutoSize = true;
            this.lblRelay2State.Location = new System.Drawing.Point(68, 53);
            this.lblRelay2State.Name = "lblRelay2State";
            this.lblRelay2State.Size = new System.Drawing.Size(21, 13);
            this.lblRelay2State.TabIndex = 11;
            this.lblRelay2State.Text = "Off";
            // 
            // lblRelay2
            // 
            this.lblRelay2.AutoSize = true;
            this.lblRelay2.Location = new System.Drawing.Point(7, 53);
            this.lblRelay2.Name = "lblRelay2";
            this.lblRelay2.Size = new System.Drawing.Size(43, 13);
            this.lblRelay2.TabIndex = 10;
            this.lblRelay2.Text = "Relay2:";
            // 
            // comboRelay2Command
            // 
            this.comboRelay2Command.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboRelay2Command.FormattingEnabled = true;
            this.comboRelay2Command.Items.AddRange(new object[] {
            "Ignore",
            "On",
            "Off",
            "Toggle"});
            this.comboRelay2Command.Location = new System.Drawing.Point(95, 50);
            this.comboRelay2Command.Name = "comboRelay2Command";
            this.comboRelay2Command.Size = new System.Drawing.Size(84, 21);
            this.comboRelay2Command.TabIndex = 9;
            // 
            // lblRelay1State
            // 
            this.lblRelay1State.AutoSize = true;
            this.lblRelay1State.Location = new System.Drawing.Point(68, 26);
            this.lblRelay1State.Name = "lblRelay1State";
            this.lblRelay1State.Size = new System.Drawing.Size(21, 13);
            this.lblRelay1State.TabIndex = 8;
            this.lblRelay1State.Text = "Off";
            // 
            // lblRelay1
            // 
            this.lblRelay1.AutoSize = true;
            this.lblRelay1.Location = new System.Drawing.Point(7, 26);
            this.lblRelay1.Name = "lblRelay1";
            this.lblRelay1.Size = new System.Drawing.Size(43, 13);
            this.lblRelay1.TabIndex = 7;
            this.lblRelay1.Text = "Relay1:";
            // 
            // comboRelay1Command
            // 
            this.comboRelay1Command.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboRelay1Command.FormattingEnabled = true;
            this.comboRelay1Command.Items.AddRange(new object[] {
            "Ignore",
            "On",
            "Off",
            "Toggle"});
            this.comboRelay1Command.Location = new System.Drawing.Point(95, 23);
            this.comboRelay1Command.Name = "comboRelay1Command";
            this.comboRelay1Command.Size = new System.Drawing.Size(84, 21);
            this.comboRelay1Command.TabIndex = 6;
            // 
            // btnWriteRelay
            // 
            this.btnWriteRelay.Location = new System.Drawing.Point(131, 139);
            this.btnWriteRelay.Name = "btnWriteRelay";
            this.btnWriteRelay.Size = new System.Drawing.Size(75, 23);
            this.btnWriteRelay.TabIndex = 5;
            this.btnWriteRelay.Text = "Wright";
            this.btnWriteRelay.UseVisualStyleBackColor = true;
            this.btnWriteRelay.Click += new System.EventHandler(this.btnWriteRelay_Click);
            // 
            // btnReadRelay
            // 
            this.btnReadRelay.Location = new System.Drawing.Point(45, 139);
            this.btnReadRelay.Name = "btnReadRelay";
            this.btnReadRelay.Size = new System.Drawing.Size(75, 23);
            this.btnReadRelay.TabIndex = 4;
            this.btnReadRelay.Text = "Read";
            this.btnReadRelay.UseVisualStyleBackColor = true;
            this.btnReadRelay.Click += new System.EventHandler(this.btnLoadRelay_Click);
            // 
            // myNotifyIcon
            // 
            this.myNotifyIcon.BalloonTipIcon = System.Windows.Forms.ToolTipIcon.Info;
            this.myNotifyIcon.BalloonTipText = "Application Still Running";
            this.myNotifyIcon.Icon = ((System.Drawing.Icon)(resources.GetObject("myNotifyIcon.Icon")));
            this.myNotifyIcon.Text = "notifyIcon1";
            this.myNotifyIcon.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.notifyIcon1_MouseDoubleClick);
            // 
            // ScheduleData
            // 
            this.ScheduleData.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.ScheduleData.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.ID,
            this.StartTime,
            this.End,
            this.Relays});
            this.ScheduleData.Location = new System.Drawing.Point(8, 3);
            this.ScheduleData.Name = "ScheduleData";
            this.ScheduleData.Size = new System.Drawing.Size(473, 357);
            this.ScheduleData.TabIndex = 9;
            // 
            // ID
            // 
            this.ID.HeaderText = "ID";
            this.ID.Name = "ID";
            this.ID.Width = 30;
            // 
            // StartTime
            // 
            this.StartTime.HeaderText = "Start Time";
            this.StartTime.Name = "StartTime";
            this.StartTime.Width = 150;
            // 
            // End
            // 
            this.End.HeaderText = "End";
            this.End.Name = "End";
            this.End.Width = 150;
            // 
            // Relays
            // 
            this.Relays.HeaderText = "Relays";
            this.Relays.Name = "Relays";
            // 
            // btnLoadSchedule
            // 
            this.btnLoadSchedule.Location = new System.Drawing.Point(8, 366);
            this.btnLoadSchedule.Name = "btnLoadSchedule";
            this.btnLoadSchedule.Size = new System.Drawing.Size(75, 23);
            this.btnLoadSchedule.TabIndex = 10;
            this.btnLoadSchedule.Text = "Load";
            this.btnLoadSchedule.UseVisualStyleBackColor = true;
            this.btnLoadSchedule.Click += new System.EventHandler(this.btnLoadSchedule_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Gainsboro;
            this.ClientSize = new System.Drawing.Size(492, 516);
            this.Controls.Add(this.myMenuStrip);
            this.Controls.Add(this.myTabControl);
            this.MainMenuStrip = this.myMenuStrip;
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.Resize += new System.EventHandler(this.Form1_Resize);
            this.myMenuStrip.ResumeLayout(false);
            this.myMenuStrip.PerformLayout();
            this.myTabControl.ResumeLayout(false);
            this.ganTab.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.Logo)).EndInit();
            this.USBTab.ResumeLayout(false);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.InternetTab.ResumeLayout(false);
            this.InternetTab.PerformLayout();
            this.ScheduleTab.ResumeLayout(false);
            this.IOTab.ResumeLayout(false);
            this.IOTab.PerformLayout();
            this.myStatusStrip.ResumeLayout(false);
            this.myStatusStrip.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ScheduleData)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip myMenuStrip;
        private System.IO.Ports.SerialPort mySerialPort;
        private System.Windows.Forms.TabControl myTabControl;
        private System.Windows.Forms.TabPage USBTab;
        private System.Windows.Forms.TabPage InternetTab;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.RichTextBox rxRichTextbox;
        private System.Windows.Forms.TabPage ScheduleTab;
        private System.Windows.Forms.TabPage ganTab;
        private System.Windows.Forms.PictureBox Logo;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.CheckBox checkBoxMinToTray;
        private System.Windows.Forms.Label lblPollTime;
        private System.Windows.Forms.ComboBox comboBoxTime;
        private System.Windows.Forms.CheckBox checkBoxStatus;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox textBox9;
        private System.Windows.Forms.TextBox textBox10;
        private System.Windows.Forms.TextBox textBox7;
        private System.Windows.Forms.TextBox textBox8;
        private System.Windows.Forms.Button button6;
        private System.Windows.Forms.NotifyIcon myNotifyIcon;
        private System.Windows.Forms.Button btnApplyUSB;
        private System.Windows.Forms.Button btnCancelUSB;
        private System.Windows.Forms.Button btnOkayUSB;
        private System.Windows.Forms.Button btnApplyInternet;
        private System.Windows.Forms.Button btnCancelInternet;
        private System.Windows.Forms.Button btnOkayInternet;
        private System.Windows.Forms.Button btnApplySchedule;
        private System.Windows.Forms.Button btnCancelSchedule;
        private System.Windows.Forms.Button btnOkaySchedule;
        private System.Windows.Forms.Button clearTxButton;
        private System.Windows.Forms.Button sendButton;
        private System.Windows.Forms.RichTextBox richTextBox1;
        private System.Windows.Forms.Button button16;
        private System.Windows.Forms.TabPage IOTab;
        private System.Windows.Forms.Button btnApplyIO;
        private System.Windows.Forms.Button btnCancelIO;
        private System.Windows.Forms.Button btnOkayIO;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Button btnWriteRelay;
        private System.Windows.Forms.Button btnReadRelay;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label statusLabel;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox baudRateCombobox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox comListComboBox;
        private System.Windows.Forms.StatusStrip myStatusStrip;
        private System.Windows.Forms.ToolStripStatusLabel statusLabelSerial;
        private System.Windows.Forms.ToolStripStatusLabel statusLabelEthernet;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel3;
        private System.Windows.Forms.Label lblRelay1;
        public System.Windows.Forms.ComboBox comboRelay1Command;
        private System.Windows.Forms.Label lblRelay4;
        public System.Windows.Forms.ComboBox comboRelay4Command;
        private System.Windows.Forms.Label lblRelay3;
        public System.Windows.Forms.ComboBox comboRelay3Command;
        private System.Windows.Forms.Label lblRelay2;
        public System.Windows.Forms.ComboBox comboRelay2Command;
        public System.Windows.Forms.Label lblRelay1State;
        public System.Windows.Forms.Label lblRelay4State;
        public System.Windows.Forms.Label lblRelay3State;
        public System.Windows.Forms.Label lblRelay2State;
        private System.Windows.Forms.DataGridView ScheduleData;
        private System.Windows.Forms.DataGridViewTextBoxColumn ID;
        private System.Windows.Forms.DataGridViewTextBoxColumn StartTime;
        private System.Windows.Forms.DataGridViewTextBoxColumn End;
        private System.Windows.Forms.DataGridViewTextBoxColumn Relays;
        private System.Windows.Forms.Button btnLoadSchedule;
    }
}

