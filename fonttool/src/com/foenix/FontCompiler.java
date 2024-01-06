package com.foenix;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.UnsupportedEncodingException;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;

import com.ssnc.util.file.FileUtil;
import com.ssnc.util.network.NetUtil;
import com.ssnc.util.string.StringUtil;

public class FontCompiler
{
	public static void main(String[] args)
	{
		if(args.length > 0)
		{
			if("-d".equals(args[0]))
			{
				System.out.println("DOWNLOAD MODE");
				if(args.length > 1)
				{
					System.out.println("DOWNLOAD URL:" + args[1]);
					
					ByteArrayOutputStream bout = new ByteArrayOutputStream();
					Map<String,String> headers = new HashMap<String,String>();
					downloadHTTPContent(args[1], headers, bout);
					
					try
					{
						String content = new String(bout.toByteArray(),"utf-8");
						content = content.substring(content.indexOf("<span class=\"title\">"));
						//System.out.println("DOWNLOAD CONTENT:\n" + content);
						
						String[] ss = content.split("<span class=\"title\">");
						for(String s : ss)
						{
							String name = s.trim().split("</span>")[0];
							if(name.length() > 0)
							{
								System.out.println(name);
								String uname = name.replaceAll(" ","%20");
								//https://download.damieng.com/fonts/zx-origins/Space%20Opera.zip\
								//https://download.damieng.com/fonts/zx-origins/ZX%20Sierra%20Quest.zip
								String url = "https://download.damieng.com/fonts/zx-origins/" + uname + ".zip";
								System.out.println(url);
								
								try
								{
									headers.clear();
									FileOutputStream fout = new FileOutputStream(name.replaceAll(" ","") + ".zip");
									downloadHTTPContent(url, headers, fout);
									fout.flush();
								}
								catch(Exception e)
								{
									// TODO Auto-generated catch block
									e.printStackTrace();
								}
							}
						}
						
					}
					catch(UnsupportedEncodingException e)
					{
						e.printStackTrace();
					}
				}
				System.exit(0);;
			}
			
			
			File t = new File(args[0]);
			if(t.exists())
			{
				File[] files = null;
				if(t.isDirectory())
				{
					files = t.listFiles();
				}
				else
				{
					files = new File[1];
					files[0] = t; 
				}
				
				for(File f : files)
				{					
					FontCompiler fc = new FontCompiler();
					if(args.length > 1)
					{
						fc.compile(f, new File(args[1]));
					}
					else
					{
						fc.compile(f);
					}
				}
			}
			else
			{
				System.out.println("Syntax Error:  Font file or directory must exist.");
			}
		}
		else
		{
			System.out.println("Syntax Error:  Must provide a font file or directory to compile.");
		}
	}
	
	public FontCompiler()
	{
		
	}
	
	
	public void compile(File sourceFile)
	{
		File filePath = sourceFile.getParentFile();
		try
		{
			System.out.println(filePath.getCanonicalPath());
			compile(sourceFile,filePath);
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}
	
	public void compile(File sourceFile, File destDir)
	{
		//String fileName = "C:\\Users\\mike.bush\\devprojects\\FXOSRenderingEngineTest\\csrc\\font\\src\\Gemma.zip";
		
		if(!destDir.isDirectory())
		{
			System.out.println("Syntax Error:  Destination must be a directory.");
			return;
		}		
		
		try
		{
			ZipFile zf = new ZipFile(sourceFile);
			if(zf!=null)
			{
				Enumeration<? extends ZipEntry> i = zf.entries();
				while(i.hasMoreElements())
				{
					ZipEntry ze = i.nextElement();
					String zen = ze.getName();
					//System.out.println(zen);
					
					if(zen.toLowerCase().startsWith("source/"))
					{
						//System.out.println("SOURCE...");
						if(zen.toLowerCase().endsWith(".h"))
						{
							String headerName = zen.split("/")[1].trim();
							String fontName = headerName.replace(" ","").replace(".h","");
							System.out.println("FOUND HEADER:" + headerName + "[" + fontName + "]");
							
							ByteArrayOutputStream bout = new ByteArrayOutputStream();
							FileUtil.copyStreamToStream(zf.getInputStream(ze), bout);
							
							byte[] bytes = bout.toByteArray();
							String content = new String(bytes, "utf-8");
							//System.out.println("FOUND CONTENT:\n" + content);		
							
							String compressed = content.replace(" ","")
									                   .replace("\t","")
									                   .replace("\r","");
							//System.out.println("FOUND COMPRESSED:\n" + compressed);
							
							int openBracket  = compressed.indexOf("{") + 1;
							int closeBracket = compressed.lastIndexOf("}");
							String raw = compressed.substring(openBracket,closeBracket);
							//System.out.println("FOUND RAW:\n" + raw);
						
							String data = "";
							
							String[] lines = raw.split("\n");
							for(String line : lines)
							{
								line = line.trim();
								if(line.length() > 0)
								{
									//System.out.println("\t-->" + line);
									
									String clean = line.substring(0,line.lastIndexOf(",//"));
									
									//System.out.println("\t--->" + clean);
									
									//if(clean.endsWith("/"))
									//	System.out.println("\t--->" + clean);
									
									
									if(data.length() > 0)
									{
										data+=",";
									}
									data+=clean;									
								}
							}
							
							//System.out.println("FOUND CLEAN:\n" + data);
							
							List<Byte> font = new ArrayList<Byte>();
							for(String token : data.split(","))
							{
								//System.out.println("TOKEN:" + token);
								int  v = Integer.parseInt(token.replace("0x",""), 16);
								byte b = (byte)v;
								//System.out.println("TOKEN(" + v + "," + b + "):" + token);
								font.add(b);
							}
							
							
							System.out.println("BYTES 1:" + font);
							
							
							ByteArrayOutputStream fbout = new ByteArrayOutputStream(); 
							
							
							
							
							int c = 0;
							byte[] fontBytes = new byte[font.size()];
							for(Byte bc : font)
							{
								fontBytes[c++] = bc;
							}	
							
							File outputFile = new File(destDir + File.separator + fontName + ".fnt");
							System.out.println("outputFile:" + outputFile.getCanonicalPath());

							fbout.write(StringUtil.padEnd("FXRZ", (char)0, 4).getBytes("utf-8"));
							fbout.write(StringUtil.padEnd("FONT", (char)0, 4).getBytes("utf-8"));
							fbout.write(8 & 0xFF);
							fbout.write(8 & 0xFF);
							fbout.write(StringUtil.padEnd(fontName,(char)0, 32).getBytes("utf-8"));
							
							fbout.write(fontBytes);							
														
							FileUtil.writeFile(outputFile, fbout.toByteArray());
							
						}

					}
				}				
			}			
		}
		catch (IOException e)
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public static int downloadHTTPContent(String address,Map<String, String> headerData,OutputStream out)
	{
		int totalRead = 0;

		try
		{
			URL host = new URL(address);

			HttpURLConnection httpConnection = (HttpURLConnection) host.openConnection();
			if(httpConnection != null)
			{
				httpConnection.setRequestMethod("GET");
				httpConnection.setInstanceFollowRedirects(true);
				httpConnection.setRequestProperty("User-Agent", "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_10_1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/41.0.2227.1 Safari/537.36");
				httpConnection.setRequestProperty("Content-Type", "text/plain; charset=UTF-8");
				httpConnection.setRequestProperty("Content-length", "0");
				
				if(headerData!=null && headerData.size() > 0)
				{
					for(String key : headerData.keySet())
					{
						String value = headerData.get(key);
						httpConnection.setRequestProperty(key, value);
					}
					headerData.clear();
				}

				httpConnection.setAllowUserInteraction(false);
				httpConnection.setUseCaches(false);
				httpConnection.setDoInput(true);
				httpConnection.setDoOutput(true);
				
				httpConnection.connect();
				
				InputStream in = httpConnection.getInputStream();
				if(in != null)
				{
					byte[] bytes = new byte[8192];

					int read = 0;
					while((read = in.read(bytes, 0, bytes.length)) > -1)
					{
						out.write(bytes, 0, read);
						totalRead += read;
					}
					out.flush();

					if(headerData != null)
					{
						Map<String, List<String>> headers = httpConnection.getHeaderFields();
						for(String key : headers.keySet())
						{
							List<String> hds = headers.get(key);
							if(hds != null && hds.size() > 0)
							{
								String data = "";
								for(String d : hds)
								{
									if(data.length() > 0)
									{
										data += " ";
									}
									data += d;
								}
								headerData.put(key, data);
							}
						}
					}

					in.close();
				}
			}

		}
		catch(Exception e)
		{
			totalRead = 0;
		}

		return totalRead;
	}
	
	
}
