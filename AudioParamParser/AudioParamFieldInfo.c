/* MediaTek Inc. (C) 2016. All rights reserved.
 *
 * Copyright Statement:
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein is
 * confidential and proprietary to MediaTek Inc. and/or its licensors. Without
 * the prior written permission of MediaTek inc. and/or its licensors, any
 * reproduction, modification, use or disclosure of MediaTek Software, and
 * information contained herein, in whole or in part, shall be strictly
 * prohibited.
 */

/*
 * Description:
 *   Implement ParamInfo & FieldInfo related APIs
 */

#include "AudioParamParserPriv.h"

EXPORT size_t paramInfoGetNumOfFieldInfo(ParamInfo *paramInfo)
{
    if (!paramInfo)
    {
        ERR_LOG("paramInfo is NULL!\n");
        return 0;
    }

    return HASH_COUNT(paramInfo->fieldInfoHash);
}

EXPORT FieldInfo *paramInfoGetFieldInfoByIndex(ParamInfo *paramInfo, size_t index)
{
    FieldInfo *fieldInfo = NULL;
    size_t i = 0;

    if (!paramInfo)
    {
        ERR_LOG("paramInfo is NULL!\n");
        return NULL;
    }

    for (fieldInfo = paramInfo->fieldInfoHash; fieldInfo ; fieldInfo = fieldInfo->hh.next)
    {
        if (index == i++)
        {
            return fieldInfo;
        }
    }

    return NULL;
}

EXPORT FieldInfo *paramInfoGetFieldInfoByName(ParamInfo *paramInfo, const char *fieldName)
{
    FieldInfo *fieldInfo;

    if (!paramInfo)
    {
        ERR_LOG("paramInfo is NULL!\n");
        return NULL;
    }

    /* Query Param name */
    HASH_FIND_STR(paramInfo->fieldInfoHash, fieldName, fieldInfo);

    return fieldInfo;
}

EXPORT ParamInfo *paramInfoCreate(const char *name, DATA_TYPE dataType, AudioType *audioType)
{
    ParamInfo *paramInfo = (ParamInfo *)malloc(sizeof(ParamInfo));
    paramInfo->audioType = audioType;
    paramInfo->name = strdup(name);
    paramInfo->dataType = dataType;
    paramInfo->fieldInfoHash = NULL;
    return paramInfo;
}

EXPORT FieldInfo *fieldInfoCreate(const char *fieldName, unsigned int arrayIndex, int startBit, int endBit, const char *checkList, ParamInfo *paramInfo)
{
    FieldInfo *fieldInfo = (FieldInfo *)malloc(sizeof(FieldInfo));

    /* Setup members */
    fieldInfo->name = strdup(fieldName);
    fieldInfo->arrayIndex = arrayIndex;
    fieldInfo->startBit = startBit;
    fieldInfo->endBit = endBit;
    fieldInfo->paramInfo = paramInfo;

    if (checkList)
    {
        fieldInfo->checkListStr = strdup(checkList);
    }
    else
    {
        fieldInfo->checkListStr = utilGenCheckList(endBit - startBit + 1);
    }

    return fieldInfo;
}

EXPORT void paramInfoRelease(ParamInfo *paramInfo)
{
    if (paramInfo == NULL)
    {
        return;
    }

    if (paramInfo->fieldInfoHash)
    {
        FieldInfo *tmp, *item;
        HASH_ITER(hh, paramInfo->fieldInfoHash, item, tmp)
        {
            HASH_DEL(paramInfo->fieldInfoHash, item);
            fieldInfoRelease(item);
        }
    }

    free(paramInfo->name);
    free(paramInfo);
}

EXPORT void fieldInfoRelease(FieldInfo *fieldInfo)
{
    if (fieldInfo == NULL)
    {
        return;
    }

    if (fieldInfo->checkListStr)
    {
        free(fieldInfo->checkListStr);
    }

    free(fieldInfo->name);
    free(fieldInfo);
}

EXPORT APP_STATUS fieldInfoGetCheckListValue(FieldInfo *fieldInfo, const char *checkName, unsigned int *checkVal)
{
    char *checkList;
    char *valStr;
    char *nameStr;
    char *restOfStr = NULL;
    if (!fieldInfo)
    {
        ERR_LOG("fieldInfo is NULL\n");
        return APP_ERROR;
    }

    if (!checkName)
    {
        ERR_LOG("checkName is NULL\n");
        return APP_ERROR;
    }

    if (!checkVal)
    {
        ERR_LOG("checkVal is NULL\n");
        return APP_ERROR;
    }

    checkList = strdup(fieldInfo->checkListStr);
    valStr = strtok_r(checkList, ARRAY_SEPERATOR, &restOfStr);
    if (!valStr)
    {
        ERR_LOG("Cannot parse valStr\n");
        free(checkList);
        return APP_ERROR;
    }

    while ((nameStr = strtok_r(NULL, ARRAY_SEPERATOR, &restOfStr)) != NULL)
    {
        if (!strcmp(nameStr, checkName))
        {
            *checkVal = strtoul(valStr, NULL, 0);
            free(checkList);
            return APP_NO_ERROR;
        }

        valStr = strtok_r(NULL, ARRAY_SEPERATOR, &restOfStr);
        if (!valStr)
        {
            ERR_LOG("Cannot parse valStr\n");
            free(checkList);
            return APP_ERROR;
        }
    }

    free(checkList);
    return APP_ERROR;
}
