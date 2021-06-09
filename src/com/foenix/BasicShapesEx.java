package com.foenix;

import java.awt.EventQueue;

import javax.swing.JFrame;

public class BasicShapesEx extends JFrame
{

	public BasicShapesEx()
	{

		initUI();
	}

	private void initUI()
	{

		add(new Rectangles());

		setTitle("Basic shapes");
		setSize(1580, 900);
		setLocationRelativeTo(null);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}

	public static void main(String[] args)
	{

		EventQueue.invokeLater(new Runnable()
		{

			@Override
			public void run()
			{
				System.out.println("run()");
				BasicShapesEx ex = new BasicShapesEx();
				ex.setVisible(true);
			}
		});
	}
}