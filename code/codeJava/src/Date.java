/**
 * @class Date
 * @brief represents a date in DD/MM/YY format
 * @var day the day
 * @var month the month
 * @var year the year
 */
public class Date {
	private int day;
	private int month;
	private int year;

	public Date (int day, int month, int year) {
		this.day = day;
		this.month = month;
		this.year = year;
	}

	/**
	 * @return the day
	 */
	public int getDay() {
		return day;
	}

	/**
	 * @return the month
	 */
	public int getMonth() {
		return month;
	}

	/**
	 * @return the year
	 */
	public int getYear() {
		return year;
	}

	/**
	 * @brief sets the day
	 */
	public void setDay(int day) {
		this.day = day;
	}

	/**
	 * @brief sets the month
	 */
	public void setMonth(int month) {
		this.month = month;
	}

	/**
	 * @brief sets the year
	 */
	public void setYear(int year) {
		this.year = year;
	}

	/**
	 * @return the date in string format DD/MM/YY
	 */
	public String toStringDate() {
		return String.format("%02d", day) + "/" + String.format("%02d", month) +
		 	"/" + String.format("%02d", year);
	}
}
