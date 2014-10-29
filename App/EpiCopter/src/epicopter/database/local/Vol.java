package epicopter.database.local;

public class Vol {

	private long	id;
	private int		picture;
	private int		video;

	public long getId() {
		return id;
	}

	public void setId(long id) {
		this.id = id;
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
		return "--id:" + id + "- -picture:" + picture + "- -video:" + video + "--";
	}
}
