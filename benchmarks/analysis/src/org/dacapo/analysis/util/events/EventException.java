package org.dacapo.analysis.util.events;

import org.dacapo.analysis.util.CSVInputStream;
import org.dacapo.instrument.LogTags;

public class EventException extends Event {

	public  static final String TAG = LogTags.LOG_PREFIX_EXCEPTION;
	
	public EventException(long time) {
		super(time);
	}
	
	public String getLogPrefix() {
		return TAG;
	}

	static Event parse(CSVInputStream is) throws EventParseException {
		throw new EventParseException("format error "+TAG);
	}
}