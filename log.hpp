#ifndef _LOG_H_
#define _LOG_H_

#define logger_str "logger"

static inline quill::Logger*
get_logger()
{
	return quill::get_logger(logger_str);
}

#endif // _LOG_H_
