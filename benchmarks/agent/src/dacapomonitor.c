#include "dacapolog.h"
#include "dacapotag.h"
#include "dacapooptions.h"
#include "dacapolock.h"
#include "dacapothread.h"

#include "dacapomonitor.h"

void monitor_init() {

}

void monitor_capabilities(const jvmtiCapabilities* availableCapabilities, jvmtiCapabilities* capabilities) {
	if (isSelected(OPT_MONITOR,NULL)) {
		capabilities->can_generate_monitor_events         = availableCapabilities->can_generate_monitor_events;
	}
}

void monitor_callbacks(const jvmtiCapabilities* capabilities, jvmtiEventCallbacks* callbacks) {
	if (capabilities->can_generate_monitor_events && isSelected(OPT_MONITOR,NULL)) {
		DEFINE_CALLBACK(callbacks,MonitorContendedEnter,JVMTI_EVENT_MONITOR_CONTENDED_ENTER);
		DEFINE_CALLBACK(callbacks,MonitorContendedEntered,JVMTI_EVENT_MONITOR_CONTENDED_ENTERED);
		DEFINE_CALLBACK(callbacks,MonitorWait,JVMTI_EVENT_MONITOR_WAIT);
		DEFINE_CALLBACK(callbacks,MonitorWaited,JVMTI_EVENT_MONITOR_WAITED);
	}
}

void monitor_logon(JNIEnv* env) {

}

void JNICALL callbackMonitorContendedEnter(jvmtiEnv *jvmti_env, JNIEnv* jni_env, jthread thread, jobject object)
{
	if (logState ) {
		jlong thread_tag = 0;
		jlong object_tag = 0;

		enterCriticalSection(&lockTag);
		jboolean thread_has_new_tag = getTag(thread, &thread_tag);
		jboolean object_has_new_tag = getTag(object, &object_tag);
		exitCriticalSection(&lockTag);

		enterCriticalSection(&lockLog);
		log_field_string(LOG_PREFIX_MONITOR_CONTENTED_ENTER);
		log_field_time();
		
		thread_log(jni_env, thread, thread_tag, thread_has_new_tag);
		
		jniNativeInterface* jni_table;
		if (object_has_new_tag) {
			if (JVMTI_FUNC_PTR(baseEnv,GetJNIFunctionTable)(baseEnv,&jni_table) != JNI_OK) {
				fprintf(stderr, "failed to get JNI function table\n");
				exit(1);
			}
		}

		log_field_jlong(object_tag);
		if (object_has_new_tag) {
			LOG_OBJECT_CLASS(jni_table,jni_env,baseEnv,object);
		} else {
			log_field_string(NULL);
		}

		log_eol();
		exitCriticalSection(&lockLog);
	}
}

void JNICALL callbackMonitorContendedEntered(jvmtiEnv *jvmti_env, JNIEnv* jni_env, jthread thread, jobject object)
{
	if (logState ) {
		jlong thread_tag = 0;
		jlong object_tag = 0;

		enterCriticalSection(&lockTag);
		jboolean thread_has_new_tag = getTag(thread, &thread_tag);
		jboolean object_has_new_tag = getTag(object, &object_tag);
		exitCriticalSection(&lockTag);

		enterCriticalSection(&lockLog);
		log_field_string(LOG_PREFIX_MONITOR_CONTENTED_ENTERED);
		log_field_time();


		thread_log(jni_env, thread, thread_tag, thread_has_new_tag);
		
		jniNativeInterface* jni_table;
		if (object_has_new_tag) {
			if (JVMTI_FUNC_PTR(baseEnv,GetJNIFunctionTable)(baseEnv,&jni_table) != JNI_OK) {
				fprintf(stderr, "failed to get JNI function table\n");
				exit(1);
			}
		}

		log_field_jlong(object_tag);
		if (object_has_new_tag) {
			LOG_OBJECT_CLASS(jni_table,jni_env,baseEnv,object);
		} else {
			log_field_string(NULL);
		}

		log_eol();
		exitCriticalSection(&lockLog);
	}
}

void JNICALL callbackMonitorWait(jvmtiEnv *jvmti_env, JNIEnv* jni_env, jthread thread, jobject object, jlong timeout)
{
	if (logState ) {
		jlong thread_tag = 0;
		jlong object_tag = 0;

		enterCriticalSection(&lockTag);
		jboolean thread_has_new_tag = getTag(thread, &thread_tag);
		jboolean object_has_new_tag = getTag(object, &object_tag);
		exitCriticalSection(&lockTag);

		enterCriticalSection(&lockLog);
		log_field_string(LOG_PREFIX_MONITOR_WAIT);
		log_field_time();

		thread_log(jni_env, thread, thread_tag, thread_has_new_tag);
		
		jniNativeInterface* jni_table;
		if (object_has_new_tag) {
			if (JVMTI_FUNC_PTR(baseEnv,GetJNIFunctionTable)(baseEnv,&jni_table) != JNI_OK) {
				fprintf(stderr, "failed to get JNI function table\n");
				exit(1);
			}
		}

		log_field_jlong(object_tag);
		if (object_has_new_tag) {
			LOG_OBJECT_CLASS(jni_table,jni_env,baseEnv,object);
		} else {
			log_field_string(NULL);
		}

		log_eol();
		exitCriticalSection(&lockLog);
	}
}

void JNICALL callbackMonitorWaited(jvmtiEnv *jvmti_env, JNIEnv* jni_env, jthread thread, jobject object, jboolean timed_out)
{
	if (logState ) {
		jlong thread_tag = 0;
		jlong object_tag = 0;

		enterCriticalSection(&lockTag);
		jboolean thread_has_new_tag = getTag(thread, &thread_tag);
		jboolean object_has_new_tag = getTag(object, &object_tag);
		exitCriticalSection(&lockTag);

		enterCriticalSection(&lockLog);
		log_field_string(LOG_PREFIX_MONITOR_WAITED);
		log_field_time();

		thread_log(jni_env, thread, thread_tag, thread_has_new_tag);

		jniNativeInterface* jni_table;
		if (object_has_new_tag) {
			if (JVMTI_FUNC_PTR(baseEnv,GetJNIFunctionTable)(baseEnv,&jni_table) != JNI_OK) {
				fprintf(stderr, "failed to get JNI function table\n");
				exit(1);
			}
		}
		
		log_field_jlong(object_tag);
		if (object_has_new_tag) {
			LOG_OBJECT_CLASS(jni_table,jni_env,baseEnv,object);
		} else {
			log_field_string(NULL);
		}
		
		log_eol();
		exitCriticalSection(&lockLog);
	}
}

