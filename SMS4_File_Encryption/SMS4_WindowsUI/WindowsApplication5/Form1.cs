using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace WindowsApplication5
{
    public partial class 文件加密软件 : Form
    {
        public 文件加密软件()
        {
            InitializeComponent();
        }

        public
            string doc, name;
            long  start, end;


        public unsafe void ByteToInt(byte[] plainBlock, uint[] temp)
        {
            int j;
            for (j = 0; j < 4; j++)
            {
                temp[j] = (uint)(plainBlock[j * 4 + 0] * 0x1000000) + (uint)(plainBlock[j * 4 + 1] * 0x10000) + (uint)(plainBlock[j * 4 + 2] * 0x100) + (uint)(plainBlock[j * 4 + 3]);
            }
        }


        public unsafe void Fill(byte[] plainBlock, char ch, uint n)
        {

            while (n < 16) { (plainBlock[n]) = (byte)ch; n++; }
        }


        public unsafe void IntToByte(byte[] cipherBlock, uint[] temp)
        {
            int j;
            for (j = 0; j < 4; j++)
            {
                cipherBlock[j * 4 + 0] = (byte)(temp[35 - j] >> 24);
                cipherBlock[j * 4 + 1] = (byte)((temp[35 - j] << 8) >> 24);
                cipherBlock[j * 4 + 2] = (byte)((temp[35 - j] << 16) >> 24);
                cipherBlock[j * 4 + 3] = (byte)((temp[35 - j] << 24) >> 24);
            }
        }


        public unsafe void KeyGenerate(byte[] baseKey, uint[] roundKey)
        {
            ByteToInt(baseKey, roundKey);
            int i,j;
            roundKey[0] ^= 0xa3b1bac6;
            roundKey[1] ^= 0x56aa3350;
            roundKey[2] ^= 0x677d9197;
            roundKey[3] ^= 0xb27022dc;
            uint[] CK = new uint[]
                     {0x00070e15,0x1c232a31,0x383f464d,0x545b6269,
                     0x70777e85,0x8c939aa1,0xa8afb6bd,0xc4cbd2d9,
                     0xe0e7eef5,0xfc030a11,0x181f262d,0x343b4249,
                     0x50575e65,0x6c737a81,0x888f969d,0xa4abb2b9,
                     0xc0c7ced5,0xdce3eaf1,0xf8ff060d,0x141b2229,
                     0x30373e45,0x4c535a61,0x686f767d,0x848b9299,
                     0xa0a7aeb5,0xbcc3cad1,0xd8dfe6ed,0xf4fb0209,
                     0x10171e25,0x2c333a41,0x484f565d,0x646b7279};
            int line, row;
            uint[] t = new uint[4];
            uint[,] s_box = new uint[,]
                                      {{0xd6,0x90,0xe9,0xfe,0xcc,0xe1,0x3d,0xb7,0x16,0xb6,0x14,0xc2,0x28,0xfb,0x2c,0x05},
                                      {0x2b,0x67,0x9a,0x76,0x2a,0xbe,0x04,0xc3,0xaa,0x44,0x13,0x26,0x49,0x86,0x06,0x99},
                                      {0x9c,0x42,0x50,0xf4,0x91,0xef,0x98,0x7a,0x33,0x54,0x0b,0x43,0xed,0xcf,0xac,0x62},
                                      {0xe4,0xb3,0x1c,0xa9,0xc9,0x08,0xe8,0x95,0x80,0xdf,0x94,0xfa,0x75,0x8f,0x3f,0xa6},
                                      {0x47,0x07,0xa7,0xfc,0xf3,0x73,0x17,0xba,0x83,0x59,0x3c,0x19,0xe6,0x85,0x4f,0xa8},
                                      {0x68,0x6b,0x81,0xb2,0x71,0x64,0xda,0x8b,0xf8,0xeb,0x0f,0x4b,0x70,0x56,0x9d,0x35},
                                      {0x1e,0x24,0x0e,0x5e,0x63,0x58,0xd1,0xa2,0x25,0x22,0x7c,0x3b,0x01,0x21,0x78,0x87},
                                      {0xd4,0x00,0x46,0x57,0x9f,0xd3,0x27,0x52,0x4c,0x36,0x02,0xe7,0xa0,0xc4,0xc8,0x9e},
                                      {0xea,0xbf,0x8a,0xd2,0x40,0xc7,0x38,0xb5,0xa3,0xf7,0xf2,0xce,0xf9,0x61,0x15,0xa1},
                                      {0xe0,0xae,0x5d,0xa4,0x9b,0x34,0x1a,0x55,0xad,0x93,0x32,0x30,0xf5,0x8c,0xb1,0xe3},
                                      {0x1d,0xf6,0xe2,0x2e,0x82,0x66,0xca,0x60,0xc0,0x29,0x23,0xab,0x0d,0x53,0x4e,0x6f},
                                      {0xd5,0xdb,0x37,0x45,0xde,0xfd,0x8e,0x2f,0x03,0xff,0x6a,0x72,0x6d,0x6c,0x5b,0x51},
                                      {0x8d,0x1b,0xaf,0x92,0xbb,0xdd,0xbc,0x7f,0x11,0xd9,0x5c,0x41,0x1f,0x10,0x5a,0xd8},
                                      {0x0a,0xc1,0x31,0x88,0xa5,0xcd,0x7b,0xbd,0x2d,0x74,0xd0,0x12,0xb8,0xe5,0xb4,0xb0},
                                      {0x89,0x69,0x97,0x4a,0x0c,0x96,0x77,0x7e,0x65,0xb9,0xf1,0x09,0xc5,0x6e,0xc6,0x84},
                                      {0x18,0xf0,0x7d,0xec,0x3a,0xdc,0x4d,0x20,0x79,0xee,0x5f,0x3e,0xd7,0xcb,0x39,0x48}};
            for (j = 0; j < 32; j++)
            {
                roundKey[j + 4] = roundKey[j + 1] ^ roundKey[j + 2] ^ roundKey[j + 3] ^ CK[j];
                for (i = 0; i < 4; i++)
                {
                     line = (int)(((roundKey[j + 4]) << (i * 8)) >> 28);//printf("%d ",line);
                     row = (int)(((roundKey[j + 4]) << (i * 8 + 4)) >> 28);//printf("%d ",row);
                    t[i] = s_box[line, row];
                }
                roundKey[j + 4] = t[0] * 0x1000000 + t[1] * 0x10000 + t[2] * 0x100 + t[3];
                roundKey[j + 4] = roundKey[j + 4] ^ ((roundKey[j + 4] << 13) | (roundKey[j + 4] >> 19)) ^ ((roundKey[j + 4] << 23) | (roundKey[j + 4] >> 9));
                roundKey[j + 4] = roundKey[j] ^ roundKey[j + 4];
            }
        }


        public unsafe void Plus(byte[] Counter)
        {
            uint[] temp = new uint[4];
            ByteToInt(Counter, temp);
            if (temp[0] == 0xffffffff)
            {
                temp[0] = 0x00000000;
                if (temp[1] == 0xffffffff)
                {
                    temp[1] = 0x00000000;
                    if (temp[2] == 0xffffffff)
                    {
                        temp[2] = 0x00000000;
                        if (temp[3] == 0xffffffff)
                            temp[3] = 0x00000000;
                        else temp[3]++;
                    }
                    else temp[2]++;
                }
                else temp[1]++;
            }
            else temp[0]++;
            IntToByte(Counter, temp);
        }

        
        public unsafe void SMS4_EncryptBlock(byte[] plainBlock, uint[] roundKey, byte[] cipherBlock)
        {
            uint[] temp = new uint[36];
            ByteToInt(plainBlock, temp);
            int i,j;
            int line, row;
            uint[] t = new uint[4];
            uint[,] s_box = new uint[,]
                                      {{0xd6,0x90,0xe9,0xfe,0xcc,0xe1,0x3d,0xb7,0x16,0xb6,0x14,0xc2,0x28,0xfb,0x2c,0x05},
                                      {0x2b,0x67,0x9a,0x76,0x2a,0xbe,0x04,0xc3,0xaa,0x44,0x13,0x26,0x49,0x86,0x06,0x99},
                                      {0x9c,0x42,0x50,0xf4,0x91,0xef,0x98,0x7a,0x33,0x54,0x0b,0x43,0xed,0xcf,0xac,0x62},
                                      {0xe4,0xb3,0x1c,0xa9,0xc9,0x08,0xe8,0x95,0x80,0xdf,0x94,0xfa,0x75,0x8f,0x3f,0xa6},
                                      {0x47,0x07,0xa7,0xfc,0xf3,0x73,0x17,0xba,0x83,0x59,0x3c,0x19,0xe6,0x85,0x4f,0xa8},
                                      {0x68,0x6b,0x81,0xb2,0x71,0x64,0xda,0x8b,0xf8,0xeb,0x0f,0x4b,0x70,0x56,0x9d,0x35},
                                      {0x1e,0x24,0x0e,0x5e,0x63,0x58,0xd1,0xa2,0x25,0x22,0x7c,0x3b,0x01,0x21,0x78,0x87},
                                      {0xd4,0x00,0x46,0x57,0x9f,0xd3,0x27,0x52,0x4c,0x36,0x02,0xe7,0xa0,0xc4,0xc8,0x9e},
                                      {0xea,0xbf,0x8a,0xd2,0x40,0xc7,0x38,0xb5,0xa3,0xf7,0xf2,0xce,0xf9,0x61,0x15,0xa1},
                                      {0xe0,0xae,0x5d,0xa4,0x9b,0x34,0x1a,0x55,0xad,0x93,0x32,0x30,0xf5,0x8c,0xb1,0xe3},
                                      {0x1d,0xf6,0xe2,0x2e,0x82,0x66,0xca,0x60,0xc0,0x29,0x23,0xab,0x0d,0x53,0x4e,0x6f},
                                      {0xd5,0xdb,0x37,0x45,0xde,0xfd,0x8e,0x2f,0x03,0xff,0x6a,0x72,0x6d,0x6c,0x5b,0x51},
                                      {0x8d,0x1b,0xaf,0x92,0xbb,0xdd,0xbc,0x7f,0x11,0xd9,0x5c,0x41,0x1f,0x10,0x5a,0xd8},
                                      {0x0a,0xc1,0x31,0x88,0xa5,0xcd,0x7b,0xbd,0x2d,0x74,0xd0,0x12,0xb8,0xe5,0xb4,0xb0},
                                      {0x89,0x69,0x97,0x4a,0x0c,0x96,0x77,0x7e,0x65,0xb9,0xf1,0x09,0xc5,0x6e,0xc6,0x84},
                                      {0x18,0xf0,0x7d,0xec,0x3a,0xdc,0x4d,0x20,0x79,0xee,0x5f,0x3e,0xd7,0xcb,0x39,0x48}};
            for (j = 0; j < 32; j++)
            {
                temp[j + 4] = temp[j + 1] ^ temp[j + 2] ^ temp[j + 3] ^ roundKey[j + 4];
                for (i = 0; i < 4; i++)
                {
                    line = (int)(((temp[j + 4]) << (i * 8)) >> 28);//printf("%d ",line);
                    row = (int)(((temp[j + 4]) << (i * 8 + 4)) >> 28);//printf("%d ",row);
                    t[i] = s_box[line, row];
                }
                temp[j + 4] = t[0] * 0x1000000 + t[1] * 0x10000 + t[2] * 0x100 + t[3];
                temp[j + 4] = temp[j + 4] ^ ((temp[j + 4] << 2) | (temp[j + 4] >> 30)) ^ ((temp[j + 4] << 10) | (temp[j+ 4] >> 22)) ^
                      ((temp[j + 4] << 18) | (temp[j + 4] >> 14)) ^ ((temp[j + 4] << 24) | (temp[j + 4] >> 8));
                temp[j + 4] = temp[j] ^ temp[j + 4];
            }
            IntToByte(cipherBlock, temp);
        }



        public unsafe void SMS4_DncryptBlock(byte[] plainBlock, uint[] roundKey, byte[] cipherBlock)
        {
            uint[] temp = new uint[36];
            ByteToInt(plainBlock, temp);
            int i, j;
            int line, row;
            uint[] t = new uint[4];
            uint[,] s_box = new uint[,]
                                      {{0xd6,0x90,0xe9,0xfe,0xcc,0xe1,0x3d,0xb7,0x16,0xb6,0x14,0xc2,0x28,0xfb,0x2c,0x05},
                                      {0x2b,0x67,0x9a,0x76,0x2a,0xbe,0x04,0xc3,0xaa,0x44,0x13,0x26,0x49,0x86,0x06,0x99},
                                      {0x9c,0x42,0x50,0xf4,0x91,0xef,0x98,0x7a,0x33,0x54,0x0b,0x43,0xed,0xcf,0xac,0x62},
                                      {0xe4,0xb3,0x1c,0xa9,0xc9,0x08,0xe8,0x95,0x80,0xdf,0x94,0xfa,0x75,0x8f,0x3f,0xa6},
                                      {0x47,0x07,0xa7,0xfc,0xf3,0x73,0x17,0xba,0x83,0x59,0x3c,0x19,0xe6,0x85,0x4f,0xa8},
                                      {0x68,0x6b,0x81,0xb2,0x71,0x64,0xda,0x8b,0xf8,0xeb,0x0f,0x4b,0x70,0x56,0x9d,0x35},
                                      {0x1e,0x24,0x0e,0x5e,0x63,0x58,0xd1,0xa2,0x25,0x22,0x7c,0x3b,0x01,0x21,0x78,0x87},
                                      {0xd4,0x00,0x46,0x57,0x9f,0xd3,0x27,0x52,0x4c,0x36,0x02,0xe7,0xa0,0xc4,0xc8,0x9e},
                                      {0xea,0xbf,0x8a,0xd2,0x40,0xc7,0x38,0xb5,0xa3,0xf7,0xf2,0xce,0xf9,0x61,0x15,0xa1},
                                      {0xe0,0xae,0x5d,0xa4,0x9b,0x34,0x1a,0x55,0xad,0x93,0x32,0x30,0xf5,0x8c,0xb1,0xe3},
                                      {0x1d,0xf6,0xe2,0x2e,0x82,0x66,0xca,0x60,0xc0,0x29,0x23,0xab,0x0d,0x53,0x4e,0x6f},
                                      {0xd5,0xdb,0x37,0x45,0xde,0xfd,0x8e,0x2f,0x03,0xff,0x6a,0x72,0x6d,0x6c,0x5b,0x51},
                                      {0x8d,0x1b,0xaf,0x92,0xbb,0xdd,0xbc,0x7f,0x11,0xd9,0x5c,0x41,0x1f,0x10,0x5a,0xd8},
                                      {0x0a,0xc1,0x31,0x88,0xa5,0xcd,0x7b,0xbd,0x2d,0x74,0xd0,0x12,0xb8,0xe5,0xb4,0xb0},
                                      {0x89,0x69,0x97,0x4a,0x0c,0x96,0x77,0x7e,0x65,0xb9,0xf1,0x09,0xc5,0x6e,0xc6,0x84},
                                      {0x18,0xf0,0x7d,0xec,0x3a,0xdc,0x4d,0x20,0x79,0xee,0x5f,0x3e,0xd7,0xcb,0x39,0x48}};
            for (j = 0; j < 32; j++)
            {
                temp[j + 4] = temp[j + 1] ^ temp[j + 2] ^ temp[j + 3] ^ roundKey[35-j];
                for (i = 0; i < 4; i++)
                {
                    line = (int)(((temp[j + 4]) << (i * 8)) >> 28);//printf("%d ",line);
                    row = (int)(((temp[j + 4]) << (i * 8 + 4)) >> 28);//printf("%d ",row);
                    t[i] = s_box[line, row];
                }
                temp[j + 4] = t[0] * 0x1000000 + t[1] * 0x10000 + t[2] * 0x100 + t[3];
                temp[j + 4] = temp[j + 4] ^ ((temp[j + 4] << 2) | (temp[j + 4] >> 30)) ^ ((temp[j + 4] << 10) | (temp[j + 4] >> 22)) ^
                      ((temp[j + 4] << 18) | (temp[j + 4] >> 14)) ^ ((temp[j + 4] << 24) | (temp[j + 4] >> 8));
                temp[j + 4] = temp[j] ^ temp[j + 4];
            }
            IntToByte(cipherBlock, temp);
        }


        private void button1_Click(object sender, EventArgs e)
        {
            RunTaskDelegate runTask = new RunTaskDelegate(RunTask);

            if (textBox1.Text == "")
            { MessageBox.Show("请选择要操作的文件", "错误", MessageBoxButtons.OK); }
            else
            {
                if ((radioButton1.Checked == false) && (radioButton2.Checked == false) && (radioButton3.Checked == false) && (radioButton4.Checked == false) && (radioButton5.Checked == false))
                { MessageBox.Show("请选择加解密模式", "错误", MessageBoxButtons.OK); }
                else
                {
                    if (radioButton1.Checked == true)
                    {
                        if (textBox2.Text.Length < 16) { MessageBox.Show("请输入16位密码", "错误", MessageBoxButtons.OK); }
                        else
                        {
                            uint count = 0;
                            uint[] roundKey = new uint[36];
                            byte[] baseKey = new byte[16];
                            byte[] plainBlock = new byte[16];
                            byte[] cipherBlock = new byte[16];
                            long len;
                            long lenth;
                            start = DateTime.Now.Ticks;
                            baseKey = Encoding.UTF8.GetBytes(textBox2.Text);
                            KeyGenerate(baseKey, roundKey);


                            string fileNamer = textBox1.Text;
                            FileStream fr = new FileStream(fileNamer, FileMode.Open);
                            string fileNamew = doc + "temp.xxx";
                            if (File.Exists(fileNamew)) { File.Delete(fileNamew); FileStream sw = File.Create(fileNamew); sw.Close(); }
                            if (!File.Exists(fileNamew)) { FileStream sw = File.Create(fileNamew); sw.Close(); }
                            FileStream fw = new FileStream(fileNamew, FileMode.Open);
                            lenth = fr.Length;
                            len = 0;
                            while (true)
                            {
                                fr.Read(cipherBlock, 0, 16);
                                SMS4_DncryptBlock(cipherBlock, roundKey, plainBlock);
                                len += 16;
                                if ((len % 160000) == 0) runTask(len, lenth);
                                if (len < lenth) fw.Write(plainBlock, 0, 16); else break;
                            }
                            if (plainBlock[15] < (byte)16)
                            {
                                for (count = (uint)(16 - plainBlock[15]); count < 15; count++)
                                    if (plainBlock[count] != '\0') break;
                            }
                            if (count == 15)
                                fw.Write(plainBlock, 0, 16 - plainBlock[15]);
                            else fw.Write(plainBlock, 0, 16);

                            fr.Close();
                            fw.Close();
                            File.Delete(textBox1.Text);
                            File.Move(doc + "temp.xxx", textBox1.Text);
                            end = DateTime.Now.Ticks;
                            MessageBox.Show("文件" + name + "已经解密完毕!" + "\n" + "文件大小: " + (lenth / 1024 / 1024).ToString() + "MB " + ((lenth / 1024) % 1024).ToString() + "KB" + "\n" + "用时: " + ((end - start) / 10000000).ToString() + "秒 " + ((end - start) / 10000).ToString() + "毫秒", "加密完成", MessageBoxButtons.OK);
                        }
                    }
                }
            }

         
        }

        private void button2_Click(object sender, EventArgs e)
        {
            int dic, len;
            OpenFileDialog opnFDlg = new OpenFileDialog();

            opnFDlg.Filter = "All Type|*.*";
            if (opnFDlg.ShowDialog() == DialogResult.OK)
            {
                textBox1.Text = opnFDlg.FileName;              
            }
            if (textBox1.Text != "")
            {
                DirectoryInfo di = new DirectoryInfo(textBox1.Text);
                dic = textBox1.Text.IndexOf(di.Name);
                len = di.Name.Length;
                name = di.Name;
                doc = textBox1.Text.Remove(dic, len);
            }
        }

        delegate void RunTaskDelegate(long sum, long lenth);

        void RunTask(long sum,long lenth)
        { 
        progressBar1.Maximum = (int)lenth;
        progressBar1.Value = (int)sum;
        }


        private void radioButton3_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void 退出ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void 介绍ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("1.SMS4是中国无线局域网应用的加密算法,本软件是该算法在文件加密中的应用，"+"\n"+"其中包含了5种加密模式(分别是:电码本模式、加密块链接模式、密码反馈模式、"+"\n"+"输出反馈模式、计数器模式)。这五种加密模式都需要输入密钥，其中加密块链"+"\n"+"接模式、密码反馈模式和输出反馈模式还需要输入初始因子(IV)，计数器模式"+"\n"+"则需要输入计数初值(CTR)"+"\n"+"2.请记住加密时使用的密钥、IV和CTR，只有拥有正确的信息才能解密"+"\n"+"3.由于作者才疏学浅，算法效率不高，因此加密百兆以上的文件需要时间较长，"+"\n"+"请见谅!","帮助",MessageBoxButtons.OK);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            RunTaskDelegate runTask = new RunTaskDelegate(RunTask);


            if (textBox1.Text == "")
            { MessageBox.Show("请选择要操作的文件", "错误", MessageBoxButtons.OK); }
            else
            {
                if ((radioButton1.Checked == false) && (radioButton2.Checked == false) && (radioButton3.Checked == false) && (radioButton4.Checked == false) && (radioButton5.Checked == false))
                { MessageBox.Show("请选择加解密模式", "错误", MessageBoxButtons.OK); }
                else
                {
                    if (radioButton1.Checked == true)
                    {
                        if (textBox2.Text.Length < 16) { MessageBox.Show("请输入16位密码", "错误", MessageBoxButtons.OK); }
                        else
                        {
                            start = DateTime.Now.Ticks;
                          
                            uint count;
                            uint[] roundKey = new uint[36];
                            byte[] baseKey = new byte[16];
                            byte[] plainBlock = new byte[16];
                            byte[] cipherBlock = new byte[16];
                            long lenth;
                            long sum=0;
                            baseKey = Encoding.UTF8.GetBytes(textBox2.Text);
                            KeyGenerate(baseKey, roundKey);


                            string fileNamer = textBox1.Text;
                            FileStream fr = new FileStream(fileNamer, FileMode.Open);
                            lenth = fr.Length;
                            string fileNamew = doc + "temp.xxx";
                            if (File.Exists(fileNamew)) { File.Delete(fileNamew); FileStream sw = File.Create(fileNamew); sw.Close(); }
                            if (!File.Exists(fileNamew)) { FileStream sw = File.Create(fileNamew); sw.Close(); }

                            FileStream fw = new FileStream(fileNamew, FileMode.Open);
                            while (true)
                            {
                                if ((count = (uint)fr.Read(plainBlock, 0, 16)) == 16)
                                {
                                    SMS4_EncryptBlock(plainBlock, roundKey, cipherBlock);
                                    fw.Write(cipherBlock, 0, 16);
                                    sum += 16;
                                    if ((sum%160000)==0)runTask(sum,lenth);
                                   

                                }
                                else
                                {
                                    if (count == 0) break;
                                    Fill(plainBlock, '\0', count);
                                    plainBlock[15] = (byte)(16 - count);
                                    SMS4_EncryptBlock(plainBlock, roundKey, cipherBlock);
                                    fw.Write(cipherBlock, 0, 16);
                                    break;
                                }
                            }
                            fr.Close();
                            fw.Close();
                            File.Delete(textBox1.Text);
                            File.Move(doc + "temp.xxx", textBox1.Text);
                            end = DateTime.Now.Ticks;
                            MessageBox.Show("文件" + name + "已经加密完毕!" + "\n" + "文件大小: " + (lenth / 1024 / 1024).ToString() + "MB " + ((lenth / 1024) % 1024).ToString() + "KB" + "\n" + "用时: " + ((end - start) / 10000000).ToString() + "秒 " + ((end - start) / 10000).ToString()+"毫秒", "加密完成", MessageBoxButtons.OK);
                            progressBar1.Maximum = 100;
                            progressBar1.Value = 0;

                        }
                    }
                }
            }
        }

        private void 声明ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("       FrozenSeason" + "\n" + "     From BUAA-SMSS" + "\n" + "FrozenSeason@163.com"+"\n"+"  2010年9月于大运村", "声明", MessageBoxButtons.OK);
        } 

    }
}