using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;
using System.Net.Sockets; // http://msdn.microsoft.com/en-us/library/system.net.sockets.udpclient.aspx for more info
using System.Threading;


namespace halForm
{

    public partial class Form1 : Form
    {

        public string globalRXString ="";

        public Form1()
        {
            InitializeComponent();
        }

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            globalRXString = mySerialPort.ReadExisting();

            if (globalRXString != "") this.Invoke(new EventHandler(DisplayText));
        }

        private void DoUpdate(object s, EventArgs e)
        {

            globalRXString = mySerialPort.ReadExisting();

            if(globalRXString != "") this.Invoke(new EventHandler(DisplayText));

        }


        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void comboBox1_MouseClick(object sender, MouseEventArgs e)
        {
            string[] portNames = SerialPort.GetPortNames();

            comListComboBox.Items.Clear();

            foreach (string port in portNames)
            {
                comListComboBox.Items.Add(port);
            }
            comListComboBox.SelectedIndex = 0;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            baudRateCombobox.SelectedIndex = 0;
            comboRelay1Command.SelectedIndex = 0;
            comboRelay2Command.SelectedIndex = 0;
            comboRelay3Command.SelectedIndex = 0;
            comboRelay4Command.SelectedIndex = 0;
            int errorCode = 0;//keep track of error code for serial connect
            for (int i = 0; errorCode != 1 && i < 4; i++)
            {
                errorCode = autoConnectSerial();
            }

            if (errorCode == 1)//We are connected to AVR
            {

            }

        }

        public int autoConnectSerial()
        {
            string[] portNames = SerialPort.GetPortNames();
            string checkPortName = "";  //will be used for checking in the loop below
            bool keepName = false;

            if (mySerialPort.IsOpen == true){
                mySerialPort.Close();
                autoConnectSerial();
                return 0;
            }
            else{
                try{
                    for (int i = 0; i < portNames.Count(); i++)
                    {

                        while ((keepName == false) && (checkPortName != portNames[i]))
                        {
                            checkPortName = portNames[i];
                            mySerialPort.PortName = portNames[i];

                            comListComboBox.Items.Clear();
                            comListComboBox.Items.Add(checkPortName);
                            comListComboBox.SelectedIndex = 0;

                            mySerialPort.BaudRate = 9600;
                            mySerialPort.DataReceived += new SerialDataReceivedEventHandler(serialPort1_DataReceived);
                            mySerialPort.Open();

                            mySerialPort.WriteLine("AT Hello;");     //Send hello to ATmega32
                            Thread.Sleep(100);
                            if (globalRXString == "AT\r\nHello Host")      //Check if the AVR Responded
                            {
                                keepName = true;//If ATMEGA responds... we know we established connection therefore we keep the comm port name
                                Thread.Sleep(100);
                                mySerialPort.WriteLine("AT TS " + ((int)(DateTime.UtcNow - new DateTime(1970, 1, 1, 0, 0, 0)).TotalSeconds - 14400) + ";");
                                statusLabel.Text = "Status: Connected";
                                button1.Text = "Disconnect";
                                return 1;
                            }
                            else mySerialPort.Close();
                            
                        }
                    }
                    return 0;

                }
                catch (System.Exception excep)
                {
                    MessageBox.Show(excep.GetType().ToString());
                    return 0;

                }
            }

        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (mySerialPort.IsOpen == false)
            {
                try
                {
                    mySerialPort.BaudRate = 9600;
                    mySerialPort.Parity = Parity.None;
                    mySerialPort.DataBits = 8;
                    mySerialPort.StopBits = StopBits.One;
                    mySerialPort.PortName = comListComboBox.SelectedItem.ToString();
                    mySerialPort.Open();
                    statusLabel.Text = "Status: Connected";
                    button1.Text = "Disconnect";
                }

                catch
                {
                    MessageBox.Show("Oops, you forgot to pick a COM port", "Error: No COM Port");
                }
            }
            else
            {
                button1.Text = "Connect";

                statusLabel.Text = "Status: Disconnected";
                try
                {
                    mySerialPort.Close();
                }
                catch { }
            }
                
        }

        private void DisplayText(object sender, EventArgs e)
        {
            rxRichTextbox.AppendText(globalRXString);
            rxRichTextbox.SelectionStart = rxRichTextbox.Text.Length;
            rxRichTextbox.ScrollToCaret();
        }

        private void Close_App(object sender, EventArgs e)
        {
            this.Close();
        }

        private void checkBox2_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBoxStatus.Checked == true)
            {
                comboBoxTime.Enabled = true;
                lblPollTime.Enabled = true;
            }

            else
            {
                comboBoxTime.Enabled = false;
                lblPollTime.Enabled = false;

            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Create setup wizard");
        }

        private void okayButton_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Impliment Okay button");
        }

        private void button5_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Impliment apply button");
        }

        private void Form1_Resize(object sender, EventArgs e)
        {
            if (FormWindowState.Minimized == this.WindowState)
            {
                myNotifyIcon.Visible = true;
                myNotifyIcon.ShowBalloonTip(250);
                this.Hide();
            }
            else if (FormWindowState.Normal == this.WindowState)
            {
                myNotifyIcon.Visible = false;
            }
        }

        private void notifyIcon1_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            this.WindowState = FormWindowState.Normal;
        }

        private void sendButton_Click(object sender, EventArgs e)
        {
            Thread.Sleep(200);
            try
            {
                mySerialPort.WriteLine(richTextBox1.Lines[0]);
            }

            catch
            {
                MessageBox.Show("Please connect to COM port before sending data.", "Error: Not Connected");
            }
        }

        private void clearTxButton_Click(object sender, EventArgs e)
        {
            richTextBox1.Text = null;
        }

        private void button16_Click(object sender, EventArgs e)
        {
            Thread.Sleep(200);
            try
            {
                string mystring = "AT TS " + ((int)(DateTime.UtcNow - new DateTime(1970, 1, 1, 0, 0, 0)).TotalSeconds - 14400) + " ";
                richTextBox1.Text = mystring;
                mySerialPort.WriteLine(mystring);
            }

            catch
            {
                MessageBox.Show("Please connect to COM port before sending data.", "Error: Not Connected");
            }
        }

        private void btnLoadRelay_Click(object sender, EventArgs e)
        {
            readRelay();
        }

        private void btnWriteRelay_Click(object sender, EventArgs e)
        {
            writeRelay();
            readRelay();
        }

        public void readRelay()
        {
            try
            {
                Thread.Sleep(100);
                mySerialPort.WriteLine("AT IR;");     //Send hello to ATmega32
                Thread.Sleep(100);
                string testString = mySerialPort.ReadExisting();
                string[] words = testString.Split(new char[] { '\r', '\n' }, StringSplitOptions.RemoveEmptyEntries);

                for (int i = 0; i < words.Length; i++)
                {
                    if (words[i] != "AT")
                    {
                        string[] words2 = words[i].Split(':');

                        if (words2[0] == "Relay1")
                        {
                            if (words2[1] == "ON") lblRelay1State.Text = "ON";
                            else lblRelay1State.Text = "Off";
                        }
                        if (words2[0] == "Relay2")
                        {
                            if (words2[1] == "ON") lblRelay2State.Text = "ON";
                            else lblRelay2State.Text = "Off";
                        }
                        if (words2[0] == "Relay3")
                        {
                            if (words2[1] == "ON") lblRelay3State.Text = "ON";
                            else lblRelay3State.Text = "Off";
                        }
                        if (words2[0] == "Relay4")
                        {
                            if (words2[1] == "ON") lblRelay4State.Text = "ON";
                            else lblRelay4State.Text = "Off";
                        }

                    }
                }

            }//end try

            catch { }
        }

        public void writeRelay()
        {
            try
            {
                if (mySerialPort.IsOpen)
                {
                    string stringToWrite = "AT IS ";
                    //Thread.Sleep(200);
                    if (comboRelay1Command.SelectedItem.ToString() == "On") stringToWrite+="RELAY1 ON ";
                    else if (comboRelay1Command.SelectedItem.ToString() == "Off") stringToWrite += "RELAY1 OFF ";
                    else if (comboRelay1Command.SelectedItem.ToString() == "Toggle") stringToWrite += "RELAY1 TOGGLE ";
                    //Thread.Sleep(200);
                    if (comboRelay2Command.SelectedItem.ToString() == "On") stringToWrite += "RELAY2 ON ";
                    else if (comboRelay2Command.SelectedItem.ToString() == "Off") stringToWrite += "RELAY2 OFF ";
                    else if (comboRelay2Command.SelectedItem.ToString() == "Toggle") stringToWrite += "RELAY2 TOGGLE ";
                    //Thread.Sleep(200);
                    if (comboRelay3Command.SelectedItem.ToString() == "On") stringToWrite += "RELAY3 ON ";
                    else if (comboRelay3Command.SelectedItem.ToString() == "Off") stringToWrite += "RELAY3 OFF ";
                    else if (comboRelay3Command.SelectedItem.ToString() == "Toggle") stringToWrite += "RELAY3 TOGGLE ";
                   // Thread.Sleep(200);
                    if (comboRelay4Command.SelectedItem.ToString() == "On") stringToWrite += "RELAY4 ON ";
                    else if (comboRelay4Command.SelectedItem.ToString() == "Off") stringToWrite += "RELAY4 OFF ";
                    else if (comboRelay4Command.SelectedItem.ToString() == "Toggle") stringToWrite += "RELAY4 TOGGLE ";
                    //Thread.Sleep(200);

                    stringToWrite += ";";

                    mySerialPort.WriteLine(stringToWrite);
                    Thread.Sleep(100);
                }

            }

            catch { MessageBox.Show("Something was not right when I tried to send the relay command so I almost died!", "Error: Sending Relay Command");}
        }

        private void btnLoadSchedule_Click(object sender, EventArgs e)
        {
            //loadSchedule();
        }

 /*       public void loadSchedule()
        {
            try
            {
                if (mySerialPort.IsOpen)
                {
                    int errorCode = 1;
                    int x = 0;
                    string Day = "";
                    string StartData = "";
                    string Duration = "";
                    string Relay = "";
                    string testString = "";


                    while (errorCode == 1)
                    {
                        //mySerialPort.DataReceived += new SerialDataReceivedEventHandler(serialPort1_DataReceived);
                        //this.Invoke(new EventHandler(DoUpdate));

                        //string blah = mySerialPort.ReadExisting();
                        string mystring = "AT SR " + x.ToString() + ";";
                        mySerialPort.WriteLine(mystring);
                        Thread.Sleep(200);
                        this.Invoke(new EventHandler(DoUpdate));
                        testString = globalRXString;
                        globalRXString = "";
                        string[] words = testString.Split(new char[] { '\r', '\n' }, StringSplitOptions.RemoveEmptyEntries);

                        for (int i = 0; i < words.Length; i++)
                        {
                            if (words[i] != "AT")
                            {
                                string[] words2 = words[i].Split(':');

                                if (words2[0] == "Code")
                                {
                                    errorCode = Convert.ToInt16(words2[1]);
                                }
                                else if (words2[0] == "Day")
                                {
                                    Day = words2[1];
                                }
                                else if (words2[0] == "StartData")
                                {
                                    StartData = words2[1];
                                }
                                else if (words2[0] == "Duration")
                                {
                                    Duration = words2[1];
                                }
                                else if (words2[0] == "Relay")
                                {
                                    Relay = words2[1];
                                    if (errorCode == 1)//Atmega says the data was valid
                                    {
                                        ScheduleData.Rows.Add(x, StartData, Duration, Relay);
                                    }
                                }

                            }
                        }

                        x++;

                    }
                }

            }

            catch { }
        }*/

    }
}
