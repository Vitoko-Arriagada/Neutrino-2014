using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;


namespace WindowsFormsApplication5
{
    public partial class Form1 : Form
    {
        public static string datos1;
        public static string datos2;
        public static string datos3;
        public static string datos4;

        public Form1()
        {
            InitializeComponent();
            groupBox1.Enabled = false;
            
        }

        private void button1_Click(object sender, EventArgs e)
        {
            String[] Puertos = System.IO.Ports.SerialPort.GetPortNames();
            comboBox1.DataSource = Puertos;
        }


        private void button2_Click(object sender, EventArgs e)
        {
            if ((comboBox1.Text == "Presione el boton ->")||(comboBox1.Text == ""))
            {
                MessageBox.Show("Debes Presionar 'Leer Puertos' y elegir uno", "My Application");

            }
            else if (comboBox2.Text == "Baudios")
            {
                MessageBox.Show("Debes elegir los baudios a usar", "My Application");
            }else if (!serialPort1.IsOpen)
            {

                button2.Text = "Desconectarse";
                label1.BackColor = Color.Green;
                label1.ForeColor = Color.White;
                label1.Text = "Conectado";
                comboBox1.Enabled = false;
                comboBox2.Enabled = false;
                button1.Enabled = false;
                groupBox1.Enabled = true;
                button12.Enabled = false;
                button11.Enabled = true;
                checkBox1.Checked = true;
                checkBox4.Checked = true;
                checkBox6.Checked = true;
                checkBox8.Checked = true;
               
                serialPort1.PortName = Convert.ToString(comboBox1.SelectedItem);
                serialPort1.BaudRate = Convert.ToInt32(comboBox2.SelectedItem);
                serialPort1.ReceivedBytesThreshold = 200;
                serialPort1.Open();
                serialPort1.DtrEnable = true;
                //Thread.Sleep(2000);
                
                
                
            }
            else
            {
                button2.Text = "Conectarse";
                label1.BackColor = Color.Red;
                label1.ForeColor = Color.Black;
                label1.Text = "Desconectado";
                comboBox1.Enabled = true;
                comboBox2.Enabled = true;
                button1.Enabled = true;
                groupBox1.Enabled = false;
                serialPort1.Close();

            }
            



        }

      

       

        private void mensajesToolStripMenuItem_Click(object sender, EventArgs e)
        {
           
        }

        private void groupBox2_Enter(object sender, EventArgs e)
        {

        }

        

        private void Form1_Load(object sender, EventArgs e)
        {
            
        }

       

        private void toolTip1_Popup(object sender, PopupEventArgs e)
        {

        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (checkBox1.Checked == true)
            {
                serialPort1.Write("b");
                textBox1.Text = serialPort1.ReadLine();
            }
            else if (checkBox2.Checked == true)
            {
                serialPort1.Write("B");
                textBox1.Text = serialPort1.ReadLine();
            }
            
           



        }

        private void button4_Click(object sender, EventArgs e)
        {
            if (checkBox1.Checked == true)
            {
                serialPort1.Write("a");
                textBox1.Text = serialPort1.ReadLine();
            }
            else if (checkBox2.Checked == true)
            {
                serialPort1.Write("A");
                textBox1.Text = serialPort1.ReadLine();
            }
            
        }

        private void button6_Click(object sender, EventArgs e)
        {
            if (checkBox4.Checked == true)
            {
                serialPort1.Write("d");
                textBox2.Text = serialPort1.ReadLine();
            }
            else if (checkBox3.Checked == true)
            {
                serialPort1.Write("D");
                textBox2.Text = serialPort1.ReadLine();
            } 
            
        }

        private void button8_Click(object sender, EventArgs e)
        {
            if (checkBox6.Checked == true)
            {
                serialPort1.Write("f");
                textBox3.Text = serialPort1.ReadLine();
            }
            else if (checkBox5.Checked == true)
            {
                serialPort1.Write("F");
                textBox3.Text = serialPort1.ReadLine();
            } 
            
        }

        private void button10_Click(object sender, EventArgs e)
        {
            if (checkBox8.Checked == true)
            {
                serialPort1.Write("h");
                textBox4.Text = serialPort1.ReadLine();
            }
            else if (checkBox7.Checked == true)
            {
                serialPort1.Write("H");
                textBox4.Text = serialPort1.ReadLine();
            } 
            
        }

        private void button5_Click(object sender, EventArgs e)
        {
            if (checkBox4.Checked == true)
            {
                serialPort1.Write("c");
                textBox2.Text = serialPort1.ReadLine();
            }
            else if (checkBox3.Checked == true)
            {
                serialPort1.Write("C");
                textBox2.Text = serialPort1.ReadLine();
            } 
            
        }

        private void button7_Click(object sender, EventArgs e)
        {
            if (checkBox6.Checked == true)
            {
                serialPort1.Write("e");
                textBox3.Text = serialPort1.ReadLine();
            }
            else if (checkBox5.Checked == true)
            {
                serialPort1.Write("E");
                textBox3.Text = serialPort1.ReadLine();
            } 
            
        }

        private void button9_Click(object sender, EventArgs e)
        {
            if (checkBox8.Checked == true)
            {
                serialPort1.Write("g");
                textBox4.Text = serialPort1.ReadLine();
            }
            else if (checkBox7.Checked == true)
            {
                serialPort1.Write("G");
                textBox4.Text = serialPort1.ReadLine();
            } 
            
        }

        private void button11_Click(object sender, EventArgs e)
        {
            serialPort1.Write("M");
            button11.Enabled = false;
            button12.Enabled = true;

        }

        private void button12_Click(object sender, EventArgs e)
        {
            serialPort1.Write("m");
            button11.Enabled = true;
            button12.Enabled = false;
        }

        private void button13_Click(object sender, EventArgs e)
        {
            serialPort1.Write("P");
           
            textBox1.Text = serialPort1.ReadLine();
            textBox2.Text = serialPort1.ReadLine();
            textBox3.Text = serialPort1.ReadLine();
            textBox4.Text = serialPort1.ReadLine();
        }

        private void button14_Click(object sender, EventArgs e)
        {
            serialPort1.Write("K");
            textBox5.Text = serialPort1.ReadLine();

        }

        private void groupBox3_Enter(object sender, EventArgs e)
        {

        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox1.Checked == true)
            {
                checkBox2.Checked = false;
            }
            
            
        }

        private void checkBox2_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox2.Checked == true)
            {
                checkBox1.Checked = false;
            }
        }

        private void checkBox4_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox4.Checked == true)
            {
                checkBox3.Checked = false;
            }
        }

        private void checkBox3_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox3.Checked == true)
            {
                checkBox4.Checked = false;
            }
        }

        private void checkBox6_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox6.Checked == true)
            {
                checkBox5.Checked = false;
            }
        }

        private void checkBox5_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox5.Checked == true)
            {
                checkBox6.Checked = false;
            }
        }

        private void checkBox8_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox8.Checked == true)
            {
                checkBox7.Checked = false;
            }
        }

        private void checkBox7_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox7.Checked == true)
            {
                checkBox8.Checked = false;
            }
        }

        private void label6_Click(object sender, EventArgs e)
        {

        }

        private void label12_Click(object sender, EventArgs e)
        {
                    }

        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            System.Diagnostics.Process.Start("mailto:veamchile@veamchile.cl");
        }

       

        
    }
}

