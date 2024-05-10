using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
using System.Xml.Linq;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.ToolBar;


namespace Serial
{
    public partial class Form1 : Form
    {
        string Datain;
        public Form1()
        {
            InitializeComponent();
            getAvailablePorts();
        }
        void getAvailablePorts()
        {
            String[] ports = SerialPort.GetPortNames();
            comboBox1.Items.AddRange(ports);
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void button3_Click(object sender, EventArgs e)
        {
            try
            {
                if (comboBox1.Text == "" || comboBox2.Text == "")
                {
                    textBox2.Text = "Please select port settings";
                }
                else
                {
                    serialPort1.PortName = comboBox1.Text;
                    serialPort1.BaudRate = Convert.ToInt32(comboBox2.Text);
                    serialPort1.Open();
                    progressBar1.Value = 100;
                    button1.Enabled = true;
                    button2.Enabled = true;
                    textBox1.Enabled = true;
                    button3.Enabled = false;
                    button4.Enabled = true;
                    textBox2.Text = "";
                    
                }
            }
            catch (UnauthorizedAccessException)
            {
                textBox2.Text = "Unauthorized Access";
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            serialPort1.Close();
            progressBar1.Value = 0;
            button1.Enabled = false;
            button2.Enabled = false;
            button4.Enabled = false;
            button3.Enabled = true;
            textBox1.Enabled = false;
            textBox1.Text = "";
            textBox2.Text = "";
        }

        private void button1_Click(object sender, EventArgs e)
        {
            textBox1.Text = "";
            textBox2.Text = "";

            string slaveid = tBoxSlaveID.Text;
            byte slaveAddress = Convert.ToByte(slaveid);
            string fcncode = fcnCode.Text;
            byte functionCode = Convert.ToByte(fcncode);
            string saddress = tBoxStartAddress.Text;
            ushort startAddress = Convert.ToUInt16(saddress);
            string nofP = tBoxNumofPoints.Text;
            ushort numberOfPoints = Convert.ToUInt16(nofP);

            //Build Message(FC03)
            if (functionCode == 3)
            {
                byte[] frame = new byte[8];
                frame[0] = slaveAddress;
                frame[1] = functionCode;
                frame[2] = (byte)(startAddress >> 8);
                frame[3] = (byte)startAddress;
                frame[4] = (byte)(numberOfPoints >> 8);
                frame[5] = (byte)numberOfPoints;

                byte[] checkSum = CRC16(frame);
                frame[6] = checkSum[0];
                frame[7] = checkSum[1];

                StringBuilder hexString = new StringBuilder();
                foreach (var item in frame)
                {
                    hexString.Append(string.Format("{0:X2} ", item));
                }
                textBox1.Text = hexString.ToString();
                serialPort1.Write(frame, 0, frame.Length);

                // delay 100ms
                System.Threading.Thread.Sleep(100);

                // doc phan hoi tu slave
                int bytesToRead = serialPort1.BytesToRead;
                if (bytesToRead > 0)
                {
                    byte[] buffer = new byte[bytesToRead];
                    serialPort1.Read(buffer, 0, bytesToRead);
                    // kiem tra CRC
                    byte[] checkRX = CRC16(buffer);
                    if ((buffer[(numberOfPoints * 2) + 5 - 2] == checkRX[0]) && (buffer[(numberOfPoints * 2) + 5 - 1] == checkRX[1]))
                    {
                        StringBuilder rxdata = new StringBuilder();
                        foreach (var item in buffer)
                        {
                            rxdata.Append(string.Format("{0:X2} ", item));
                        }
                        textBox2.Text = rxdata.ToString();
                    }
                    else
                    {
                        textBox2.Text = "CRC Error";
                    }
                }
                else
                {
                    textBox2.Text = "Error";
                }
            }
            if (functionCode == 16)
            {
                string value_str = tBoxValue.Text;
                string[] value_spl = value_str.Split();
                List<int> dataValues;
                dataValues = value_spl.Select(val => Convert.ToInt32(val.Substring(0), 16)).ToList();

                int stt = 6;
                int len = numberOfPoints * 2 + 9;
                byte[] frame = new byte[len];
                frame[0] = slaveAddress;
                frame[1] = functionCode;
                frame[2] = (byte)(startAddress >> 8);
                frame[3] = (byte)startAddress;
                frame[4] = (byte)(numberOfPoints >> 8);
                frame[5] = (byte)numberOfPoints;
                frame[6] = (byte)(numberOfPoints*2);
                foreach (int value in dataValues)
                {
                    stt++;
                    frame[stt] = (byte)(value>>8);
                    stt++;
                    frame[stt] = (byte)value;
                }

                byte[] checkSum = CRC16(frame);
                frame[len-2] = checkSum[0];
                frame[len-1] = checkSum[1];

                StringBuilder hexString = new StringBuilder();
                foreach (var item in frame)
                {
                    hexString.Append(string.Format("{0:X2} ", item));
                }
                textBox1.Text = hexString.ToString();
                serialPort1.Write(frame, 0, frame.Length);

                // delay 100ms
                System.Threading.Thread.Sleep(100);

                // doc phan hoi tu slave
                int bytesToRead = serialPort1.BytesToRead;
                if (bytesToRead > 0)
                {
                    byte[] buffer = new byte[bytesToRead];
                    serialPort1.Read(buffer, 0, bytesToRead);
                    // kiem tra CRC
                    byte[] checkRX = CRC16(buffer);
                    if ((buffer[8 - 2] == checkRX[0]) && (buffer[8 - 1] == checkRX[1]))
                    {
                        StringBuilder rxdata = new StringBuilder();
                        foreach (var item in buffer)
                        {
                            rxdata.Append(string.Format("{0:X2} ", item));
                        }
                        textBox2.Text = rxdata.ToString();
                    }
                    else
                    {
                        textBox2.Text = "CRC Error";
                    }
                }
                else
                {
                    textBox2.Text = "Error";
                }
            }
        }

        private static byte[] CRC16(byte[] data)
        {
            byte[] checkSum = new byte[2];
            ushort reg_crc = 0XFFFF;
            for (int i = 0; i < data.Length - 2; i++)
            {
                reg_crc ^= data[i];
                for (int j = 0; j < 8; j++)
                {
                    if ((reg_crc & 0x01) == 1)
                    {
                        reg_crc = (ushort)((reg_crc >> 1) ^ 0xA001);
                    }
                    else
                    {
                        reg_crc = (ushort)(reg_crc >> 1);
                    }
                }
            }
            checkSum[1] = (byte)((reg_crc >> 8) & 0xFF);
            checkSum[0] = (byte)(reg_crc & 0xFF);
            return checkSum;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                //textBox2.Text = serialPort1.ReadLine();
                /*Datain = serialPort1.ReadExisting();
                textBox2.Text += Datain;*/
            }
            catch (TimeoutException)
            {
                textBox2.Text = "Timeout Exception";
            }
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void fcnCode_TextChanged(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void d1On_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                try
                {
                    string slaveid = tBoxSlaveID.Text;
                    byte slaveAddress = Convert.ToByte(slaveid);
                    string fcncode = fcnCode.Text;
                    byte functionCode = Convert.ToByte(fcncode);
                    string saddress = tBoxStartAddress.Text;
                    ushort startAddress = Convert.ToUInt16(saddress);
                    string nofP = tBoxNumofPoints.Text;
                    ushort numberOfPoints = Convert.ToUInt16(nofP);

                    //Build Message(FC16)
                    if (functionCode == 16)
                    {
                        //string value_str = tBoxValue.Text;
                        string value_str = "0000";
                        string[] value_spl = value_str.Split();
                        List<int> dataValues;
                        dataValues = value_spl.Select(val => Convert.ToInt32(val.Substring(0), 16)).ToList();

                        int stt = 6;
                        int len = numberOfPoints * 2 + 9;
                        byte[] frame = new byte[len];
                        frame[0] = slaveAddress;
                        frame[1] = functionCode;
                        frame[2] = (byte)(startAddress >> 8);
                        frame[3] = (byte)startAddress;
                        frame[4] = (byte)(numberOfPoints >> 8);
                        frame[5] = (byte)numberOfPoints;
                        frame[6] = (byte)(numberOfPoints * 2);
                        foreach (int value in dataValues)
                        {
                            stt++;
                            frame[stt] = (byte)(value >> 8);
                            stt++;
                            frame[stt] = (byte)value;
                        }

                        byte[] checkSum = CRC16(frame);
                        frame[len - 2] = checkSum[0];
                        frame[len - 1] = checkSum[1];

                        StringBuilder hexString = new StringBuilder();
                        foreach (var item in frame)
                        {
                            hexString.Append(string.Format("{0:X2} ", item));
                        }
                        textBox1.Text = hexString.ToString();
                        serialPort1.Write(frame, 0, frame.Length);

                        // delay 100ms
                        System.Threading.Thread.Sleep(100);

                        // doc phan hoi tu slave
                        int bytesToRead = serialPort1.BytesToRead;
                        if (bytesToRead > 0)
                        {
                            byte[] buffer = new byte[bytesToRead];
                            serialPort1.Read(buffer, 0, bytesToRead);
                            // kiem tra CRC
                            byte[] checkRX = CRC16(buffer);
                            if ((buffer[8 - 2] == checkRX[0]) && (buffer[8 - 1] == checkRX[1]))
                            {
                                StringBuilder rxdata = new StringBuilder();
                                foreach (var item in buffer)
                                {
                                    rxdata.Append(string.Format("{0:X2} ", item));
                                }
                                textBox2.Text = rxdata.ToString();
                            }
                            else
                            {
                                textBox2.Text = "CRC Error";
                            }
                        }
                        else
                        {
                            textBox2.Text = "Error";
                        }
                    }
                    d1Off.Enabled = true;
                    d1On.Enabled = false;
                }
                catch (Exception error)
                {
                    MessageBox.Show(error.Message);
                }
            }
        }

        private void d1Off_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                try
                {
                    string slaveid = tBoxSlaveID.Text;
                    byte slaveAddress = Convert.ToByte(slaveid);
                    string fcncode = fcnCode.Text;
                    byte functionCode = Convert.ToByte(fcncode);
                    string saddress = tBoxStartAddress.Text;
                    ushort startAddress = Convert.ToUInt16(saddress);
                    string nofP = tBoxNumofPoints.Text;
                    ushort numberOfPoints = Convert.ToUInt16(nofP);

                    //Build Message(FC16)
                    if (functionCode == 16)
                    {
                        //string value_str = tBoxValue.Text;
                        string value_str = "0001";
                        string[] value_spl = value_str.Split();
                        List<int> dataValues;
                        dataValues = value_spl.Select(val => Convert.ToInt32(val.Substring(0), 16)).ToList();

                        int stt = 6;
                        int len = numberOfPoints * 2 + 9;
                        byte[] frame = new byte[len];
                        frame[0] = slaveAddress;
                        frame[1] = functionCode;
                        frame[2] = (byte)(startAddress >> 8);
                        frame[3] = (byte)startAddress;
                        frame[4] = (byte)(numberOfPoints >> 8);
                        frame[5] = (byte)numberOfPoints;
                        frame[6] = (byte)(numberOfPoints * 2);
                        foreach (int value in dataValues)
                        {
                            stt++;
                            frame[stt] = (byte)(value >> 8);
                            stt++;
                            frame[stt] = (byte)value;
                        }

                        byte[] checkSum = CRC16(frame);
                        frame[len - 2] = checkSum[0];
                        frame[len - 1] = checkSum[1];

                        StringBuilder hexString = new StringBuilder();
                        foreach (var item in frame)
                        {
                            hexString.Append(string.Format("{0:X2} ", item));
                        }
                        textBox1.Text = hexString.ToString();
                        serialPort1.Write(frame, 0, frame.Length);

                        // delay 100ms
                        System.Threading.Thread.Sleep(100);

                        // doc phan hoi tu slave
                        int bytesToRead = serialPort1.BytesToRead;
                        if (bytesToRead > 0)
                        {
                            byte[] buffer = new byte[bytesToRead];
                            serialPort1.Read(buffer, 0, bytesToRead);
                            // kiem tra CRC
                            byte[] checkRX = CRC16(buffer);
                            if ((buffer[8 - 2] == checkRX[0]) && (buffer[8 - 1] == checkRX[1]))
                            {
                                StringBuilder rxdata = new StringBuilder();
                                foreach (var item in buffer)
                                {
                                    rxdata.Append(string.Format("{0:X2} ", item));
                                }
                                textBox2.Text = rxdata.ToString();
                            }
                            else
                            {
                                textBox2.Text = "CRC Error";
                            }
                        }
                        else
                        {
                            textBox2.Text = "Error";
                        }
                    }
                    d1On.Enabled = true;
                    d1Off.Enabled = false;
                }
                catch (Exception error)
                {
                    MessageBox.Show(error.Message);
                }
            }
        }

        private void d2On_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                try
                {
                    string slaveid = tBoxSlaveID.Text;
                    byte slaveAddress = Convert.ToByte(slaveid);
                    string fcncode = fcnCode.Text;
                    byte functionCode = Convert.ToByte(fcncode);
                    string saddress = tBoxStartAddress.Text;
                    ushort startAddress = Convert.ToUInt16(saddress);
                    string nofP = tBoxNumofPoints.Text;
                    ushort numberOfPoints = Convert.ToUInt16(nofP);

                    //Build Message(FC16)
                    if (functionCode == 16)
                    {
                        //string value_str = tBoxValue.Text;
                        string value_str = "0002";
                        string[] value_spl = value_str.Split();
                        List<int> dataValues;
                        dataValues = value_spl.Select(val => Convert.ToInt32(val.Substring(0), 16)).ToList();

                        int stt = 6;
                        int len = numberOfPoints * 2 + 9;
                        byte[] frame = new byte[len];
                        frame[0] = slaveAddress;
                        frame[1] = functionCode;
                        frame[2] = (byte)(startAddress >> 8);
                        frame[3] = (byte)startAddress;
                        frame[4] = (byte)(numberOfPoints >> 8);
                        frame[5] = (byte)numberOfPoints;
                        frame[6] = (byte)(numberOfPoints * 2);
                        foreach (int value in dataValues)
                        {
                            stt++;
                            frame[stt] = (byte)(value >> 8);
                            stt++;
                            frame[stt] = (byte)value;
                        }

                        byte[] checkSum = CRC16(frame);
                        frame[len - 2] = checkSum[0];
                        frame[len - 1] = checkSum[1];

                        StringBuilder hexString = new StringBuilder();
                        foreach (var item in frame)
                        {
                            hexString.Append(string.Format("{0:X2} ", item));
                        }
                        textBox1.Text = hexString.ToString();
                        serialPort1.Write(frame, 0, frame.Length);

                        // delay 100ms
                        System.Threading.Thread.Sleep(100);

                        // doc phan hoi tu slave
                        int bytesToRead = serialPort1.BytesToRead;
                        if (bytesToRead > 0)
                        {
                            byte[] buffer = new byte[bytesToRead];
                            serialPort1.Read(buffer, 0, bytesToRead);
                            // kiem tra CRC
                            byte[] checkRX = CRC16(buffer);
                            if ((buffer[8 - 2] == checkRX[0]) && (buffer[8 - 1] == checkRX[1]))
                            {
                                StringBuilder rxdata = new StringBuilder();
                                foreach (var item in buffer)
                                {
                                    rxdata.Append(string.Format("{0:X2} ", item));
                                }
                                textBox2.Text = rxdata.ToString();
                            }
                            else
                            {
                                textBox2.Text = "CRC Error";
                            }
                        }
                        else
                        {
                            textBox2.Text = "Error";
                        }
                    }
                    d2Off.Enabled = true;
                    d2On.Enabled = false;
                }
                catch (Exception error)
                {
                    MessageBox.Show(error.Message);
                }
            }
        }

        private void d2Off_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                try
                {
                    string slaveid = tBoxSlaveID.Text;
                    byte slaveAddress = Convert.ToByte(slaveid);
                    string fcncode = fcnCode.Text;
                    byte functionCode = Convert.ToByte(fcncode);
                    string saddress = tBoxStartAddress.Text;
                    ushort startAddress = Convert.ToUInt16(saddress);
                    string nofP = tBoxNumofPoints.Text;
                    ushort numberOfPoints = Convert.ToUInt16(nofP);

                    //Build Message(FC16)
                    if (functionCode == 16)
                    {
                        //string value_str = tBoxValue.Text;
                        string value_str = "0003";
                        string[] value_spl = value_str.Split();
                        List<int> dataValues;
                        dataValues = value_spl.Select(val => Convert.ToInt32(val.Substring(0), 16)).ToList();

                        int stt = 6;
                        int len = numberOfPoints * 2 + 9;
                        byte[] frame = new byte[len];
                        frame[0] = slaveAddress;
                        frame[1] = functionCode;
                        frame[2] = (byte)(startAddress >> 8);
                        frame[3] = (byte)startAddress;
                        frame[4] = (byte)(numberOfPoints >> 8);
                        frame[5] = (byte)numberOfPoints;
                        frame[6] = (byte)(numberOfPoints * 2);
                        foreach (int value in dataValues)
                        {
                            stt++;
                            frame[stt] = (byte)(value >> 8);
                            stt++;
                            frame[stt] = (byte)value;
                        }

                        byte[] checkSum = CRC16(frame);
                        frame[len - 2] = checkSum[0];
                        frame[len - 1] = checkSum[1];

                        StringBuilder hexString = new StringBuilder();
                        foreach (var item in frame)
                        {
                            hexString.Append(string.Format("{0:X2} ", item));
                        }
                        textBox1.Text = hexString.ToString();
                        serialPort1.Write(frame, 0, frame.Length);

                        // delay 100ms
                        System.Threading.Thread.Sleep(100);

                        // doc phan hoi tu slave
                        int bytesToRead = serialPort1.BytesToRead;
                        if (bytesToRead > 0)
                        {
                            byte[] buffer = new byte[bytesToRead];
                            serialPort1.Read(buffer, 0, bytesToRead);
                            // kiem tra CRC
                            byte[] checkRX = CRC16(buffer);
                            if ((buffer[8 - 2] == checkRX[0]) && (buffer[8 - 1] == checkRX[1]))
                            {
                                StringBuilder rxdata = new StringBuilder();
                                foreach (var item in buffer)
                                {
                                    rxdata.Append(string.Format("{0:X2} ", item));
                                }
                                textBox2.Text = rxdata.ToString();
                            }
                            else
                            {
                                textBox2.Text = "CRC Error";
                            }
                        }
                        else
                        {
                            textBox2.Text = "Error";
                        }
                    }
                    d2On.Enabled = true;
                    d2Off.Enabled = false;
                }
                catch (Exception error)
                {
                    MessageBox.Show(error.Message);
                }
            }
        }
    }
}
