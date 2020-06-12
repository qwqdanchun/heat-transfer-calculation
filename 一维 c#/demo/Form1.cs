using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;

namespace demo
{
    
    public partial class Form1 : Form
    {
        double[] T1 = new double[7];
        double[] T2 = new double[7];
        double lamda, s_h, ru;
        double delta_t, delta_x;
        double endtemp;
        public int Num;
        public Form1()
        {
            InitializeComponent();
        }

        private void 准备ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            
            for (int i = 1; i < 6; i++) 
            {
                Graphics g = CreateGraphics();
                int red = 255;
                Color color = Color.FromArgb(red, 0, 0);
                Brush MyBrush = new SolidBrush(color);
                int eagelenth = 50;
                g.FillRectangle(MyBrush, 200 + i * eagelenth, 200, eagelenth, eagelenth);
            }
                
        }

        private void 计算ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            new Thread(new ThreadStart(Cal)).Start();
        }
        public void Cal()
        {
            int i;
            int endflag;
            double themprop;
            long j;
            double delay;
            T1[0] = 300;
            T1[6] = 300;
            for (i = 1; i < 6; i++)
                T1[i] = 1370;
            lamda = 52;
            s_h = 600;
            ru = 7200;
            delta_x = 0.01;
            endtemp = 750;
            endflag = 0;
            delta_t = 0.01 * s_h * ru * delta_x * delta_x / (2 * lamda);
            themprop = lamda * delta_t / (s_h * ru * delta_x * delta_x);
            while (endflag == 0)
            {
                for (i = 1; i < 6; i++)
                    T2[i] = themprop * (T1[i - 1] + (1 / themprop - 2) * T1[i] + T1[i + 1]);
                //MessageBox.Show(Convert.ToString(T2[i]));
                for (i = 1; i < 6; i++)
                    draw(i, T2[i], endtemp);
                for (i = 1; i < 6; i++)
                {
                    endflag = 1;
                    if (T2[i] >= 750)
                    {
                        endflag = 0;
                        break;
                    }
                }
                for (i = 1; i < 6; i++) T1[i] = T2[i];
                delay = 0.0;
                for (j = 1; j < 3000000; j++)
                    delay = delay * i;
            }
            MessageBox.Show("计算完成");
            return;
        }
        public void draw(int i, double temp, double endtemp)
        {
            Graphics g = CreateGraphics();
            int red;
            if (temp - endtemp>0) 
            {
                red = Convert.ToInt32(255 * (temp - endtemp) / (1370 - endtemp));
            }
            else 
            {
                red = 0;
            }
            Color color = Color.FromArgb(red, 0, 0);
            Brush MyBrush = new SolidBrush(color);
            int eagelenth = 50;
            g.FillRectangle(MyBrush, 200 + i * eagelenth, 200, eagelenth, eagelenth);
        }
    }
}
