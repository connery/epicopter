package epicopter.database.local;

public class Vol {

	private long	id;
	private String	name;
	private String	userName;
	private int		picture;
	private int		video;

	public long getId() {
		return id;
	}

	public void setId(long id) {
		this.id = id;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getUserName() {
		return userName;
	}

	public void setUserName(String userName) {
		this.userName = userName;
	}

	public int getPicture() {
		return picture;
	}

	public void setPicture(int picture) {
		this.picture = picture;
	}

	public int getVideo() {
		return video;
	}

	public void setVideo(int video) {
		this.video = video;
	}

	@Override
	public String toString() {
		return "--id:" + id + "- -name:" + name + "- -picture:" + picture + "- -video:" + video + "--";
	}
}
