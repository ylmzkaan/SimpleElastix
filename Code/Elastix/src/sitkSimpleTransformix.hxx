#ifndef __sitksimpletransformix_hxx_
#define __sitksimpletransformix_hxx_

#include "sitkSimpleTransformix.h"
 
namespace itk {
  namespace simple {

template< typename TMovingImage >
Image
SimpleTransformix::ExecuteInternal( void )
{
  typedef elastix::TransformixFilter< TMovingImage > TransformixFilterType;
  typedef typename TransformixFilterType::Pointer TransforimxFilterPointer;

  try
  {
    TransforimxFilterPointer transformixFilter = TransformixFilterType::New();

    if( !this->IsEmpty( this->m_MovingImage ) ) {
      transformixFilter->SetInput( static_cast< TMovingImage* >( this->GetMovingImage().GetITKBase() ) );
    }

    transformixFilter->SetInputPointSetFileName( this->GetMovingPointSetFileName() );
    transformixFilter->SetComputeSpatialJacobian( this->GetComputeSpatialJacobian() );
    transformixFilter->SetComputeDeterminantOfSpatialJacobian( this->GetComputeDeterminantOfSpatialJacobian() );
    transformixFilter->SetComputeDeformationField( this->GetComputeDeformationField() );

    transformixFilter->SetOutputDirectory( this->GetOutputDirectory() );
    transformixFilter->SetLogFileName( this->GetLogFileName() );
    transformixFilter->SetLogToFile( this->GetLogToFile() );
    transformixFilter->SetLogToConsole( this->GetLogToConsole() );

    ParameterObjectPointer parameterObject = ParameterObjectType::New();
    parameterObject->SetParameterMap( this->m_TransformParameterMapVector );
    transformixFilter->SetTransformParameterObject( parameterObject );

    if( !this->IsEmpty( this->GetMovingImage() ) )
    {
      this->m_ResultImage = Image( transformixFilter->GetOutput() );
    }

    transformixFilter->Update();
  }
  catch( itk::ExceptionObject &e )
  {
    sitkExceptionMacro( << e );
  }

  return this->m_ResultImage;
}

} // end namespace simple
} // end namespace itk

#endif // __sitksimpletransformix_hxx_